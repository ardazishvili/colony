#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normals;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 boneWeights;

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gBones[MAX_BONES];
uniform bool animated;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

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
  fragPos = vec3(model * vec4(position, 1.0));
  normal = mat3(transpose(inverse(model))) * normals;
  texCoords = textureCoordinates;
}
