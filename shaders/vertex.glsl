#version 120

attribute vec3 vertexPos_modelspace;

void main()
{
  gl_Position = vec4(vertexPos_modelspace, 1.0);
}
