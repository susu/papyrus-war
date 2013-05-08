#version 330

uniform vec4 currentColor;

varying float intensity;

void main()
{
  vec4 color = currentColor;
  // if ( intensity > 1.20 )
  //   color = vec4(0.2,0.6,0.8,0.0);

  gl_FragColor = color;
}
