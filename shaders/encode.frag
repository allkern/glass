// Encoder or Modulator
// This pass converts RGB colors on iChannel0 to
// a YIQ (NTSC) Composite signal.

#define PI   3.14159265358979323846
#define TAU  6.28318530717958647693

// Hue adjustment, I've found that rotating the hue
// by -0.15° yields nicer colors, though its not really
// necessary. Change this value to your liking
#define HUE_ADJUSTMENT (-0.15)

const mat3 rgb_to_yiq = mat3(0.299, 0.596, 0.211,
                             0.587,-0.274,-0.523,
                             0.114,-0.322, 0.312);

// Alternative RGB to YIQ matrix
// const mat3 rgb_to_yiq = mat3(0.299, 0.587, 0.114,
//                              0.596,-0.274,-0.322,
//                              0.211,-0.523, 0.312);

float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

float hash13(vec3 p3)
{
	p3  = fract(p3 * .1031);
    p3 += dot(p3, p3.zyx + 31.32);
    return fract((p3.x + p3.y) * p3.z);
}

// Multipower ramping function
// t -> Target value on e
// s -> Start of ramp
// e -> End of ramp
// p -> Power (shape of curve, 1 = linear, 2 = quadratic, etc.)
// x -> Value
float ramp(float t, float s, float e, float p, float x) {
    float value = (t / pow(e - s, p)) * pow(x - s, p);

    return (value <= 0.0) ? 0.0 : value;
}

float inverted_ramp(float t, float s, float e, float p, float x) {
    float value = (t / pow((-e) + s, p)) * pow(x - ((2.0 * e) + s), p);

    return (value <= 0.0) ? 0.0 : value;
}

float mirrored_ramp(float t, float s, float e, float p, float x) {
    float r = ramp(t, s, e, p, x);
    float i = inverted_ramp(t, s, e, p, x);
    float v = (r >= t) ? i : r;
    
    return (v <= 0.0) ? 0.0 : v;
}

#define NOISE_STRENGTH (((mouse.x / resolution.x) * 4.0) + mirrored_ramp(0.25, mouse.y - 100.0, mouse.y, 2.0, resolution.y - frag_coord.y))

void main() {
    // Chroma encoder oscillator frequency 
    float fc = 400.0;
    
    // Base oscillator angle for this dot
    float t = float(frag_coord.x);

    float noise_strength = NOISE_STRENGTH;
    
    // Get a pixel from iChannel0
    float noise_y = hash12(vec2(float(int(frag_coord.y) >> 1), float(frame))) * noise_strength;
    float noise_x = hash13(vec3(frag_coord.xy, float(frame))) * noise_strength;
    float noise = noise_x + noise_y;

    vec2 pos = vec2(mod(frag_coord.x + (noise_y * noise_strength), resolution.x), frag_coord.y);
    
    float y2 = float(int(frag_coord.y) >> 1);

    if (y2 <= 3.0) {
        pos.x += (y2 * 16.0);
        pos.x -= 16.0 * 3.0;
    }

    vec3 rgb = texture(input_texture, pos / resolution.xy).rgb;

    // Convert to YIQ
    vec3 yiq = rgb_to_yiq * rgb;
    
    // Final oscillator angle
    float freq_noise_factor = PI / (5.0 / noise_strength);
    float f = fc * t + ((noise * freq_noise_factor) - freq_noise_factor) + (PI * 0.65);

    // Modulate IQ signals
    float i = yiq.y * cos(f), // I signal
          q = yiq.z * sin(f); // Q signal
    
    // Add to Y to get the composite signal
    float c = yiq.x + (i + q) + 0.1; // Composite
    
    float y_noise = hash13(vec3(frag_coord.xy, float(frame))) * (noise_strength - 1.15) * 10.0;
    
    if (y_noise <= (((noise_strength - 1.15) * 10.0) - 8.0)) {
        c *= (y_noise / 10.0) / (noise_strength - 1.15) + 1.0;
    }
    
    //if (abs((resolution.x / 2.0) - frag_coord.x) >= (resolution.x / 2.5)) {
    //    frag_color = vec4(0.0);
    //} else {
        // Return a grayscale representation of the signal
        frag_color = vec4(vec3(c), 1.0);
    //}
}