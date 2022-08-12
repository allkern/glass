void main() {
    vec2 flipped = vec2(frag_coord.x, resolution.y - frag_coord.y) / resolution.xy;
    vec2 scaled = flipped;

    frag_color = texture(input_texture, scaled);
}