#version 130

in vec3 inPosition;
in vec3 inCoord;
in vec3 inNormal;

uniform mat4 MVP;
uniform mat4 normalMatrix;

smooth out vec3 vNormal;

void main()
{
  gl_Position = MVP * vec4(inPosition, 1.0);
  vec4 vRes = normalMatrix * vec4(inNormal, 0.0);
  vNormal = vRes.xyz;
}
