
attribute vec2 pos;
varying vec2 texcoord;
varying vec2 screencoord;
uniform float width, height;
uniform vec2 texsize;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	texcoord = sign(pos) * vec2(0.5*width/texsize.x, -0.5*height/texsize.y) + vec2(0.5*width/texsize.x, 0.5*height/texsize.y);
	screencoord = sign(pos);
}