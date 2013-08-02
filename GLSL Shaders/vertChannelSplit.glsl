#version 120

uniform float leftDisplace;
uniform float rightDisplace;

void main () {
  // Split texture coordinate into 3 channels
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_TexCoord[1] = gl_MultiTexCoord0 - vec4(.01f, 0.f, 0.f, 0.f);
  gl_TexCoord[2] = gl_MultiTexCoord0 + vec4(.03f, 0.f, 0.f, 0.f);
  // Position vertex
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;;
  // Color pixel
  gl_FrontColor = gl_Color;
  gl_BackColor = vec4(0.f);
}