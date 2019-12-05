#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normals;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 boneWeights;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gBones[MAX_BONES];
uniform bool animated;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

flat out vec3 normals_colour;


vec3 calculateLighting() {
  fragPos = vec3(model * vec4(position, 1.0));
  normal = mat3(transpose(inverse(model))) * normals;
  texCoords = textureCoordinates;

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

  vec3 norm = normalize(normal);
  vec3 lightDirection = normalize(light.position - fragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, texCoords));

  vec3 viewDirection = normalize(viewPos - fragPos);
  vec3 reflectDirection = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 
		   material.shininess);
  vec3 specular = spec * light.specular * vec3(texture(material.specular, texCoords));
  
  return ambient + diffuse + specular;
}

void main()
{
  vec4 PosL;
  if (animated) {
    mat4 BoneTransform = gBones[boneIds[0]] * boneWeights[0];
    BoneTransform     += gBones[boneIds[1]] * boneWeights[1];
    BoneTransform     += gBones[boneIds[2]] * boneWeights[2];
    BoneTransform     += gBones[boneIds[3]] * boneWeights[3];
    PosL    = BoneTransform * vec4(position, 1.0);
  } else {
    PosL = vec4(position, 1.0);
  }
  gl_Position = projection * view * model * PosL;
  normals_colour = calculateLighting();
}
