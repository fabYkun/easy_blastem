
attribute vec2 pos;
varying vec2 texcoord;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	texcoord = sign(pos) * vec2(0.5, -0.5) + vec2(0.5, 0.5);
}
