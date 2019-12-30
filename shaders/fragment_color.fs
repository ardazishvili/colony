#version 330 core

uniform vec3 camPosition;
uniform float b; 
uniform float e;
uniform float h;

in vec3 worldPos;
flat in vec4 normals_colour;
in vec3 lightAmbient;

out vec4 FragColor;

vec3 applyFog(in vec3 rgb, 
              in float distance,
              in vec3 camPosition,
              in vec3 camToPointVec) {
  float bc = b;
  float ec = e;
  float c = ec / bc;
  vec3 fogColor = vec3(0.5,0.6,0.7);
  return rgb * exp( -distance * ec) + 
         fogColor * (1.0 - exp( -distance * bc));
}

void main()
{
  float alpha = normals_colour.w;

  float d = distance(worldPos, camPosition);
  vec3 camToPointVec = worldPos - camPosition;
  vec3 rgb = applyFog(normals_colour.xyz, d, camPosition, camToPointVec);

  FragColor = vec4(rgb, alpha);
}
