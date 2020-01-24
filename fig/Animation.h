#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <vector>

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Timer.h"

struct BoneData
{
  glm::mat4 offset;
  glm::mat4 transformation;
};

using BonesData = std::vector<BoneData>;
using BoneMapping = std::map<std::string, unsigned int>;
class Animation
{
public:
  enum class Direction { Forward, Backward };

  enum class Type { Permanent, OneShot };

  Animation() = delete;
  Animation(BonesData& boneInfos,
            BoneMapping& boneMapping,
            unsigned int& numBones);

  void setScene(const aiScene* scene);
  void animate(Shader& shader, Type type, float percent);

private:
  void readNodes(float time,
                 const aiNode* node,
                 const glm::mat4& parentTransform);
  void calcInterpolatedScaling(aiVector3D& Out,
                               float time,
                               const aiNodeAnim* node);
  void calcInterpolatedRotation(aiQuaternion& Out,
                                float time,
                                const aiNodeAnim* node);
  void calcInterpolatedPosition(aiVector3D& Out,
                                float time,
                                const aiNodeAnim* node);
  uint findScaling(float time, const aiNodeAnim* node);
  uint findRotation(float time, const aiNodeAnim* node);
  uint findPosition(float time, const aiNodeAnim* node);
  const aiNodeAnim* findNodeAnim(const aiAnimation* animation,
                                 const std::string nodeName);

  const aiScene* _scene;
  BonesData& _bonesData;
  BoneMapping& _boneMapping;
  unsigned int& _numBones;
  glm::mat4 _globalInverseTransform;
  Timer _timer;
  float _duration;
};

glm::mat4 mat4From3x3(const aiMatrix3x3& in);
glm::mat4 mat4From4x4(const aiMatrix4x4& in);

#endif
