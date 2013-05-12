#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inCoord;
layout (location = 2) in vec3 inNormal;

uniform mat4 MVP;
uniform mat4 normalMatrix;

smooth out vec3 vNormal;

void main()
{
  gl_Position = MVP * vec4(inPosition, 1.0);
  vec4 vRes = normalMatrix * vec4(inNormal, 0.0);
  vNormal = vRes.xyz;
}
