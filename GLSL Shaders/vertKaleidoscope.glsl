#version 120

uniform float leftDisplace;
uniform float rightDisplace;
uniform vec2 resolution;

void main () {
  // Split texture coordinate into 3 channels
  vec4 pos = 2.f * gl_MultiTexCoord0;
  gl_TexCoord[0] = pos;
  // Position vertex
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;;
  // Color pixel
  gl_FrontColor = gl_Color;
  gl_BackColor = vec4(0.f);
}