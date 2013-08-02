#version 120

#define ARRAY_SIZE 4

uniform vec2 points[ARRAY_SIZE];
uniform vec4 colors[ARRAY_SIZE];
uniform float alpha;

vec4 gray(vec4 pixel) {
  float g = dot(pixel.rgb, vec3(.28, .5, .32));
  return vec4(g, g, g, pixel.a);
}

vec4 mix(vec4 col1, vec4 col2, float a) {
  a = max(a, 0.f);
  a = min(a, 1.f);
  return max(a * col2 + (1-a) * col1, vec4(.2f));
}

void main() {
  // Get the pixel position
  vec2 pixel_position = gl_TexCoord[0].st;
  
  // First iteration of loop to find default value
  float smallest_distance = distance(points[0], pixel_position);
  vec2 closest_point = points[0];
  vec4 closest_color = colors[0];
  
  float total_distance = 0.f;
  vec4 mix_color = vec4(0.f);
  
  // Iterate through loops
  for (int k = 0; k < ARRAY_SIZE; k++) {
    mix_color = mix_color + colors[k] / distance(points[k], pixel_position) / 1.;
  }
  
  //
  vec4 a = gray(mix_color), b = mix_color/ARRAY_SIZE;
  gl_FragColor =  mix(a, (1.f + alpha/5.f) * b, alpha);
}