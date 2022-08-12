void main() {
	gl_Position = gl_Vertex;

	vec2 normalized = (gl_Position.xy + vec2(1.0)) / 2.0;

	frag_coord = normalized * resolution.xy;
}