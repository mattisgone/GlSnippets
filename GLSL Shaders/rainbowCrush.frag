#version 120

/**
 * Parametric Distortion with Perlin Noise for Scan Lines
 * Based on https://www.shadertoy.com/view/MssGW7
 * @author Matt Owen & https://www.shadertoy.com/view/MssGW7
 * @since 2013-07-26
 */
uniform sampler2D texture;
uniform vec2 resolution;
uniform float time;
uniform float alpha;
uniform vec4 leftColor;
uniform vec4 rightColor;

float hash(float n) {
  return fract(sin(n) * 43758.5453123f);
}
float noise1(float x) {
  float p = floor(x);
  float f = fract(x);
  f = f*f*(3.0-2.0*f);
  return mix( hash(p+0.0), hash(p+1.0), f );
}
float fbm(float p) {
  float f = 0.0;
  f += 0.5f * noise1(p);
  p = 2.02f * p;
  f += 0.25f * noise1(p);
  p = 2.03f * p;
  f += 0.1250f * noise1(p);
  p = 2.01f * p;
  f += 0.0625f * noise1( p );
  return f/0.9375f;
}
vec4 mix (vec4 rgba, vec4 r, vec4 gb) {
  return leftColor * r + rightColor * gb;
}

void main() {
	vec2 uv = gl_FragCoord.xy/resolution.xy;
	float c = dot(
                vec3(
                     fbm(uv.y * 5.134/2 + time * 20.013),
                     fbm(uv.y * 15.002/2 + time * 3.591),
                     fbm(uv.y * 25.922/2 + time * 4.277)
                     ),
                vec3(.85, .35, .17)
                );
  c /= 4.f;
  //
  vec2 coord = mod(gl_TexCoord[0].xy, resolution);
  vec2 leftCoord = mod(gl_TexCoord[0].xy + alpha/2.f * vec2(c, 0.f), vec2(1.f, 1.f));
  vec2 rightCoord = mod(gl_TexCoord[0].xy + alpha/2.f * vec2(c/2.f, 0.f), vec2(1.f, 1.f));
  //
  vec4 rgba_channel = texture2D(texture, resolution * gl_TexCoord[0].xy);
  vec4 red_channel = texture2D(texture, leftCoord);
  vec4 cyan_channel = texture2D(texture, rightCoord);
  
	gl_FragColor = mix(rgba_channel, red_channel, cyan_channel);
  // gl_FragColor = vec4(0.f, 1.f, 1.f, 1.f);
}