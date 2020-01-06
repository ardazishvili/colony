#version 330 core

uniform vec3 camPosition;
uniform float fog_b; 
uniform float fog_e;
uniform float fog_h;
uniform float water_b; 
uniform float water_e;
uniform float water_h;

in vec3 worldPos;
flat in vec4 normals_colour;
in vec3 lightAmbient;

out vec4 FragColor;

vec3 applyFog(in vec3 rgb, 
              in vec3 camPosition,
              in vec3 camToPointVec) {
  float maxWaterHeight = water_h;
  vec3 waterColor = vec3(0.0,0.8,1.0);
  /* vec3 waterColor = vec3(0.0); */
  float distInWater = maxWaterHeight - worldPos.z;
  float waterAmount = (log(distInWater * water_e) - 1) * water_b;
  waterAmount = clamp(waterAmount, 0, 1);
  vec3 tmp = mix(rgb, waterColor, waterAmount);

  float maxFogHeight = fog_h;
  vec3 fogColor = vec3(0.5,0.6,0.7);
  float distInFog = maxFogHeight - worldPos.z;
  float fogAmount = (log(distInFog * fog_e) - 1) * fog_b;
  fogAmount = clamp(fogAmount, 0, 1);
  return mix(tmp, fogColor, fogAmount);
}

void main()
{
  float alpha = normals_colour.w;

  float d = distance(worldPos, camPosition);
  vec3 camToPointVec = worldPos - camPosition;
  vec3 rgb = applyFog(normals_colour.xyz, camPosition, camToPointVec);

  FragColor = vec4(rgb, alpha);
}
