#version 120

uniform sampler2D texture;

// 1D-Texture specifying displacement distance
uniform sampler1D noise;

uniform vec2 resolution;
uniform float time;

vec4 mix (vec4 rgb, vec4 r, vec4 gb) {
  r.gb = vec2(0.f);
  gb.r = 0.f;
  
  return r + gb;
}

void main () {
  vec4 rgba_channel = texture2D(texture, gl_TexCoord[0].xy);
  vec4 red_channel = texture2D(texture, gl_TexCoord[1].xy);
  vec4 cyan_channel = texture2D(texture, gl_TexCoord[2].xy);
  
  gl_FragColor = mix(rgba_channel, red_channel, cyan_channel);
}