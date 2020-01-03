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
              in vec3 camPosition,
              in vec3 camToPointVec) {

  float maxFogHeight = h;

  /* vec3 fogColor = vec3(0.5,0.6,0.7); */
  vec3 fogColor = vec3(0.0,0.8,1.0);
  float distance = length(camToPointVec);
  if(worldPos.z >= maxFogHeight - 1 / e)
  {		
      return rgb;
  }
  
  float distInFog = distance * (maxFogHeight - worldPos.z) / 
                               (camPosition.z - worldPos.z );
  float fogAmount = (log(distInFog * e) - 1) * b;
  fogAmount = clamp(fogAmount, 0, 1);
  return mix(rgb, fogColor, fogAmount);
}

void main()
{
  float alpha = normals_colour.w;

  float d = distance(worldPos, camPosition);
  vec3 camToPointVec = worldPos - camPosition;
  vec3 rgb = applyFog(normals_colour.xyz, camPosition, camToPointVec);

  FragColor = vec4(rgb, alpha);
}
