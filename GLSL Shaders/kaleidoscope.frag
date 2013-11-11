#version 120

uniform vec2 resolution;
uniform float time;
uniform sampler2DRect texture;
uniform bool isArb = false;


void main() {
  vec2 pos = gl_TexCoord[0].xy;

  if (pos.x > 1.f) {
    pos.x = 2.f - pos.x;
  }
  
  if (pos.y > 1.f) {
    pos.y = 2.f - pos.y;
  }
  
  vec4 pixel = texture2DRect(texture, pos * resolution);
  
	gl_FragColor = pixel;
}