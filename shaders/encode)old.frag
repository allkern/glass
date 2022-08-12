// Encoder or Modulator
// This pass converts RGB colors on input_texture to
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

void main() {
    // Chroma encoder oscillator frequency 
    float fc = 400.0;
    
    // Base oscillator angle for this dot
    float t = float(frag_coord.x);
    
    // Get a pixel from input_texture
    float noise_y = hash12(vec2(float(int(frag_coord.y) >> 1), float(frame))) * (1.0 + 0.0 * 100.0);
    float noise_x = hash13(vec3(frag_coord.xy, float(frame))) * (1.0 + 0.0);
    float noise = noise_x + noise_y;

    vec2 pos = vec2(mod(frag_coord.x + noise_y - 0.0, resolution.x), frag_coord.y);
    
    float y2 = float(int(frag_coord.y) >> 1);

    if (y2 <= 3.0) {
        pos.x += (y2 * 16.0);
        pos.x -= 16.0 * 3.0;
    }

    vec3 rgb = texture(input_texture, pos / resolution.xy).rgb;

    // Convert to YIQ
    vec3 yiq = rgb_to_yiq * rgb;
    
    // Final oscillator angle
    float f = fc * t + (noise * (PI / 10.0)) + (PI * 0.65);

    // Modulate IQ signals
    float i = yiq.y * cos(f), // I signal
          q = yiq.z * sin(f); // Q signal
    
    // Add to Y to get the composite signal
    float c = yiq.x + (i + q) + 0.1; // Composite
    
    //if (abs((resolution.x / 2.0) - frag_coord.x) >= (resolution.x / 3.0)) {
    //    frag_color = vec4(0.0);
    //} else {
        // Return a grayscale representation of the signal
        frag_color = vec4(vec3(c), 1.0);
    //}
}