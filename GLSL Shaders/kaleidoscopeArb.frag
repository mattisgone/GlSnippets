#version 120

#define M_PI 3.14159

uniform sampler2DRect texture;
uniform vec2 resolution;
uniform int level;
uniform vec3 color;

vec2 kaleidoscope (vec2 p) {
  vec2 uv;
  p = 2.f * p - 1.f;
  float a = atan(p.y, p.x);
  float r = length(p);
  float time =  0.f;
  uv.x =  7.0 * a / 3.1416;
  uv.y = -time+ sin(7.0*r+time) + .7*cos(time+7.0*a);
  float w = .5+.5*(sin(time+7.0*r)+ .7*cos(time+7.0*a));
  return uv;
}
vec2 rotate (vec2 p, float angle) {
  p.xy -= .5f;
  return mat2(cos(angle), -sin(angle), sin(angle), cos(angle)) * p + .5f;;
}
vec2 flume (vec2 p) {
  p *= 2.f;
  p.x = p.x > 1.f ? 2.f - p.x : p.x;
  p.y = p.y > 1.f ? 2.f - p.y : p.y;
  return p;
}

void main() {
  vec2 pos0 = flume(gl_TexCoord[0].xy);
  vec2 pos1 = flume(gl_TexCoord[1].xy);
  vec2 pos2 = flume(gl_TexCoord[2].xy);
  vec2 pos3 = flume(gl_TexCoord[3].xy);
  
  vec4 pixel;
  if (pos3.x >= 0.f && pos3.x <= 1.f && pos3.y >= 0.f && pos3.y <= 1.f) {
    pixel = texture2DRect(texture, pos3 * resolution);
  }
  else if (pos2.x >= 0.f && pos2.x <= 1.f && pos2.y >= 0.f && pos2.y <= 1.f) {
    pixel = texture2DRect(texture, pos2 * resolution);
  }
  else if (pos1.x >= 0.f && pos1.x <= 1.f && pos1.y >= 0.f && pos1.y <= 1.f) {
    pixel = texture2DRect(texture, pos1 * resolution);
  }
  else {
    pixel = texture2DRect(texture, pos0 * resolution);
  }
  // ...
  float g = dot(pixel.rgb, vec3(.28, .5, .32));
  // ...
  // gl_FragColor = pixel;
  gl_FragColor.rgb = g * color;
  gl_FragColor.a = pixel.a;
}