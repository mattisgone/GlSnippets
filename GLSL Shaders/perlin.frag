#version 120

uniform sampler2D texture;
uniform float time;
//
// Description : Array and textureless GLSL 2D/3D/4D simplex
//               noise functions.
//      Author : Ian McEwan, Ashima Arts.
//  Maintainer : ijm
//     Lastmod : 20110822 (ijm)
//     License : Copyright (C) 2011 Ashima Arts. All rights reserved.
//               Distributed under the MIT License. See LICENSE file.
//               https://github.com/ashima/webgl-noise
//

vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
  return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r) {
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v) {
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);
  
  // First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;
  
  // Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );
  
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y
  
  // Permutations
  i = mod289(i);
  vec4 p = permute(permute(
                           permute(i.z + vec4(0.0, i1.z, i2.z, 1.0 )) + i.y + vec4(0.0, i1.y, i2.y, 1.0 )
                           )
                   + i.x + vec4(0.0, i1.x, i2.x, 1.0)
                   );
  
  // Gradients: 7x7 points over a square, mapped onto an octahedron.
  // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;
  
  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)
  
  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)
  
  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);
  
  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );
  
  
  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));
  
  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;
  
  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);
  
  //Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;
  
  // Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1),
                               dot(p2,x2), dot(p3,x3) ) );
}

float fbm (vec3 pos, int octaves, float lacunarity, float gain) {
  float sum = 0.0;
  float amp = 1.0;
  
  for(int i = 0; i < octaves; i+=1) {
    amp *= gain;
    sum += amp * snoise(pos);
    pos *= lacunarity;
  }
  
  return sum;
}

/*
float pattern(in vec2 p) {
  float l = 2.5;
  float g = 0.4;
  int oc = 10;
  
  vec2 q = vec2( fbm( p + vec2(0.0,0.0),oc,l,g),fbm( p + vec2(5.2,1.3),oc,l,g));
  vec2 r = vec2( fbm( p + 4.0*q + vec2(1.7,9.2),oc,l,g ), fbm( p + 4.0*q + vec2(8.3,2.8) ,oc,l,g));
  return fbm( p + 4.0*r ,oc,l,g);
}

float pattern2( in vec2 p, out vec2 q, out vec2 r , in float time)
{
  float l = 2.3;
  float g = 0.4;
  int oc = 10;
  
  q.x = fbm( p + vec2(time,time),oc,l,g);
  q.y = fbm( p + vec2(5.2*time,1.3*time) ,oc,l,g);
  
  r.x = fbm( p + 4.0*q + vec2(1.7,9.2),oc,l,g );
  r.y = fbm( p + 4.0*q + vec2(8.3,2.8) ,oc,l,g);
  
  return fbm( p + 4.0*r ,oc,l,g);
}
 */

float contour (float val) {
  return val > .15f ? 1.f : 0.f;
}

void main() {
  //  vec3 q = vec3(gl_FragCoord.x/150, gl_FragCoord.y/150, 1.f * time/1.f/pow(gl_FragCoord.x, .5f));
  vec3 q = vec3(gl_FragCoord.x/150, gl_FragCoord.y/150, time/5.f);
  float color = 3.5f * fbm(q, 3, 2.5f, .6f);
  
  vec3 c = vec3(0.f, color, color);
  
  //float k = contour(color);
  //vec3 c = vec3(1.f, 1.f, 1.f) * k + vec3(0.f, 1.f, 1.f) * (1-k);
  
  gl_FragColor.rgb = c;
  gl_FragColor.a = 1.f;
}