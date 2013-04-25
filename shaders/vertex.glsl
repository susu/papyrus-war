#version 130

attribute vec3 vertexPos_modelspace;

uniform mat4 MVP;

const vec3 lightDir = vec3(3.0, 2.0, 1.2);

varying float intensity;

void main()
{
  intensity = dot( lightDir, gl_Normal );
  gl_Position = MVP * vec4(vertexPos_modelspace, 1.0);
}
