
uniform sampler2D textures[2];
uniform vec2 texsize;

varying vec2 texcoord;

void main()
{
	float x0 = (floor(texcoord.x * texsize.x - 0.25) + 0.5)/texsize.x;
	float x1 = (floor(texcoord.x * texsize.x + 0.25) + 0.5)/texsize.x;
	float y0 = (floor(texcoord.y * texsize.y + 0.25) + 0.5)/texsize.y;
	float y1 = (floor(texcoord.y * texsize.y - 0.25) + 0.5)/texsize.y;
	
	float ymix = (sin(texcoord.y * texsize.y * 6.283185307) + 1.0) * 0.5;
	float xmix = (sin(texcoord.x * texsize.x * 6.283185307) + 1.0) * 0.5;
	gl_FragColor = mix(
		mix(
			texture2D(textures[1], vec2(x0, y1)),
			texture2D(textures[0], vec2(x0, y0)),
			ymix
		),
		mix(
			texture2D(textures[1], vec2(x1, y1)),
			texture2D(textures[0], vec2(x1, y0)),
			ymix
		),
		xmix
	);
}
