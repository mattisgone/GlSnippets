#version 120
/**
 *
 */
#define PI 3.14159
//
uniform float shift = 0.2f;
uniform float spin = PI/4.f;
//
vec4 remap (vec4 coord, float s) {
  float b = 1.f / (1 - 2 * s);
  float a = -s * b;
  return a + b * coord;
}
//
vec4 rotate (vec4 coord, float angle) {
  vec2 p = coord.xy - .5f;
  p = mat2(cos(angle), -sin(angle), sin(angle), cos(angle)) * p + .5f;
  return vec4(p.x, p.y, coord.z, coord.a);
}
//
void main () {
  // Split texture coordinate into 3 channels
  gl_TexCoord[0] = ((gl_MultiTexCoord0));
  gl_TexCoord[1] = rotate(remap(gl_MultiTexCoord0, shift), spin);
  gl_TexCoord[2] = rotate(remap(gl_MultiTexCoord0, 2.f * shift), 2.f * spin);
  gl_TexCoord[3] = rotate(remap(gl_MultiTexCoord0, 2.5f * shift), 3.f * spin);
  // Position vertex
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;;
  // Color pixel
  gl_FrontColor = gl_Color;
  gl_BackColor = vec4(0.f);
}