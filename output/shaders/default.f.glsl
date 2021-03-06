
uniform sampler2D textures[2];
uniform vec2 texsize;

varying vec2 texcoord;

void main()
{
	vec2 modifiedCoord0 = vec2(texcoord.x, (floor(texcoord.y * texsize.y + 0.25) + 0.5)/texsize.y);
	vec2 modifiedCoord1 = vec2(texcoord.x, (floor(texcoord.y * texsize.y - 0.25) + 0.5)/texsize.y);
	gl_FragColor = mix(
		texture2D(textures[1], modifiedCoord1),
		texture2D(textures[0], modifiedCoord0),
		(sin(texcoord.y * texsize.y * 6.283185307) + 1.0) * 0.5
	);
}
