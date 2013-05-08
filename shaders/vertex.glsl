#version 330

attribute vec3 vertexPos_modelspace;

layout (location = 1) in vec3 diffuseColor;

uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(vertexPos_modelspace, 1.0);
}
