#version 120

attribute vec3 vertexPos_modelspace;

uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(vertexPos_modelspace, 1.0);
}
