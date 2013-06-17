#version 130

smooth in vec3 vNormal;
out vec4 outputColor;

uniform vec4 currentColor;

struct SimpleDirectLight
{
  vec3 vColor;
  vec3 vDirection;
  float fAmbientIntensity;
};

uniform SimpleDirectLight sunLight;

void main()
{
  float diffuseIntensity = clamp( dot( normalize(vNormal), -normalize(sunLight.vDirection) ), 0.0, 1.0 );

  float intensity = sunLight.fAmbientIntensity + diffuseIntensity;
  vec4 lightColor = vec4( sunLight.vColor * intensity, 1.0 );
  outputColor = currentColor * lightColor;
}
