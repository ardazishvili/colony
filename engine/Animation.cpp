#include <algorithm>

#include "Animation.h"

Animation::Animation(BonesData& bonesData,
                     BoneMapping& boneMapping,
                     unsigned int& numBones) :
  _bonesData(bonesData),
  _boneMapping(boneMapping), _numBones(numBones)
{}

void Animation::setScene(const aiScene* scene)
{
  _scene = scene;
  _globalInverseTransform = mat4From4x4(_scene->mRootNode->mTransformation);
  _globalInverseTransform = glm::inverse(_globalInverseTransform);
  if (_scene->HasAnimations()) {
    _duration = static_cast<float>(_scene->mAnimations[0]->mDuration);
  }
}

void Animation::animate(Shader& shader, Type type, float percent)
{
  float TimeInSeconds =
    std::chrono::duration_cast<std::chrono::milliseconds>(_timer.elapsed())
      .count() /
    1000.0f;
  if (type == Animation::Type::OneShot) {
    TimeInSeconds =
      std::min(TimeInSeconds, _duration * ::abs(percent) - 0.00001f);
  }
  std::vector<glm::mat4> transforms;
  transforms.resize(_numBones);

  float time = ::abs(percent) * _duration;
  float timePoint;
  if (percent > 0) {
    timePoint = time;
  } else if (percent < 0) {
    timePoint = _duration - time;
  }
  glm::mat4 identity(1.0f);
  readNodes(timePoint, _scene->mRootNode, identity);
  for (unsigned int i = 0; i < _numBones; i++) {
    transforms[i] = _bonesData[i].transformation;
  }
  shader.setBool("animated", true);
  for (uint i = 0; i < transforms.size(); i++) {
    transforms[i] = glm::transpose(transforms[i]);
    shader.setBoneTransform(i, transforms[i]);
  }
}

unsigned int Animation::findPosition(float time, const aiNodeAnim* node)
{
  for (unsigned int i = 0; i < node->mNumPositionKeys - 1; i++) {
    if (time < (float)node->mPositionKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);

  return 0;
}

unsigned int Animation::findRotation(float time, const aiNodeAnim* node)
{
  assert(node->mNumRotationKeys > 0);

  for (unsigned int i = 0; i < node->mNumRotationKeys - 1; i++) {
    if (time < (float)node->mRotationKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);

  return 0;
}

unsigned int Animation::findScaling(float time, const aiNodeAnim* node)
{
  assert(node->mNumScalingKeys > 0);

  for (unsigned int i = 0; i < node->mNumScalingKeys - 1; i++) {
    if (time < (float)node->mScalingKeys[i + 1].mTime) {
      return i;
    }
  }

  assert(0);

  return 0;
}

void Animation::calcInterpolatedPosition(aiVector3D& out,
                                         float time,
                                         const aiNodeAnim* node)
{
  if (node->mNumPositionKeys == 1) {
    out = node->mPositionKeys[0].mValue;
    return;
  }

  unsigned int index = findPosition(time, node);
  unsigned int nextIndex = index + 1;
  assert(nextIndex < node->mNumPositionKeys);
  float deltaTime = (float)(node->mPositionKeys[nextIndex].mTime -
                            node->mPositionKeys[index].mTime);
  float factor = (time - (float)node->mPositionKeys[index].mTime) / deltaTime;
  assert(factor >= 0.0f && factor <= 1.0f);
  const aiVector3D& start = node->mPositionKeys[index].mValue;
  const aiVector3D& end = node->mPositionKeys[nextIndex].mValue;
  aiVector3D delta = end - start;
  out = start + factor * delta;
}

void Animation::calcInterpolatedRotation(aiQuaternion& out,
                                         float time,
                                         const aiNodeAnim* node)
{
  if (node->mNumRotationKeys == 1) {
    out = node->mRotationKeys[0].mValue;
    return;
  }

  unsigned int index = findRotation(time, node);
  unsigned int nextIndex = index + 1;
  assert(nextIndex < node->mNumRotationKeys);
  float deltaTime = (float)(node->mRotationKeys[nextIndex].mTime -
                            node->mRotationKeys[index].mTime);
  float factor = (time - (float)node->mRotationKeys[index].mTime) / deltaTime;
  assert(factor >= 0.0f && factor <= 1.0f);
  const aiQuaternion& startRotationQ = node->mRotationKeys[index].mValue;
  const aiQuaternion& endRotationQ = node->mRotationKeys[nextIndex].mValue;
  aiQuaternion::Interpolate(out, startRotationQ, endRotationQ, factor);
  out = out.Normalize();
}

void Animation::calcInterpolatedScaling(aiVector3D& out,
                                        float time,
                                        const aiNodeAnim* node)
{
  if (node->mNumScalingKeys == 1) {
    out = node->mScalingKeys[0].mValue;
    return;
  }

  unsigned int index = findScaling(time, node);
  unsigned int nextIndex = index + 1;
  assert(nextIndex < node->mNumScalingKeys);
  float deltaTime = (float)(node->mScalingKeys[nextIndex].mTime -
                            node->mScalingKeys[index].mTime);
  auto t = (float)node->mScalingKeys[index].mTime;
  float factor = (time - t) / deltaTime;
  assert(factor >= 0.0f && factor <= 1.0f);
  const aiVector3D& start = node->mScalingKeys[index].mValue;
  const aiVector3D& end = node->mScalingKeys[nextIndex].mValue;
  aiVector3D delta = end - start;
  out = start + factor * delta;
}

void Animation::readNodes(float time,
                          const aiNode* node,
                          const glm::mat4& parentTransform)
{
  std::string nodeName(node->mName.data);

  const aiAnimation* animation = _scene->mAnimations[0];

  glm::mat4 nodeTransformation = mat4From4x4(node->mTransformation);

  const aiNodeAnim* animationNode = findNodeAnim(animation, nodeName);

  if (animationNode) {
    aiVector3D scaleFactor;
    calcInterpolatedScaling(scaleFactor, time, animationNode);

    aiQuaternion rotationQuaternion;
    calcInterpolatedRotation(rotationQuaternion, time, animationNode);
    glm::mat4 rotationMatrix = mat4From3x3(rotationQuaternion.GetMatrix());

    aiVector3D translation;
    calcInterpolatedPosition(translation, time, animationNode);

    auto mat = glm::mat4(1.0);
    mat = glm::translate(
      mat, glm::vec3(translation.x, translation.y, translation.z));
    mat = mat * rotationMatrix;
    mat =
      glm::scale(mat, glm::vec3(scaleFactor.x, scaleFactor.y, scaleFactor.z));
    nodeTransformation = mat;
  }
  glm::mat4 globalTransformation = parentTransform * nodeTransformation;

  if (_boneMapping.find(nodeName) != _boneMapping.end()) {
    unsigned int BoneIndex = _boneMapping[nodeName];
    _bonesData[BoneIndex].transformation = _globalInverseTransform *
                                           globalTransformation *
                                           _bonesData[BoneIndex].offset;
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    readNodes(time, node->mChildren[i], globalTransformation);
  }
}

const aiNodeAnim* Animation::findNodeAnim(const aiAnimation* animation,
                                          const std::string nodeName)
{
  for (unsigned int i = 0; i < animation->mNumChannels; i++) {
    const aiNodeAnim* node = animation->mChannels[i];

    if (std::string(node->mNodeName.data) == nodeName) {
      return node;
    }
  }

  return NULL;
}

glm::mat4 mat4From3x3(const aiMatrix3x3& in)
{
  auto m = glm::mat4();
  m[0][0] = in.a1;
  m[1][0] = in.a2;
  m[2][0] = in.a3;
  m[3][0] = 0.0f;

  m[0][1] = in.b1;
  m[1][1] = in.b2;
  m[2][1] = in.b3;
  m[3][1] = 0.0f;

  m[0][2] = in.c1;
  m[1][2] = in.c2;
  m[2][2] = in.c3;
  m[3][2] = 0.0f;

  m[0][3] = 0.0f;
  m[1][3] = 0.0f;
  m[2][3] = 0.0f;
  m[3][3] = 1.0f;

  return m;
}

glm::mat4 mat4From4x4(const aiMatrix4x4& in)
{
  auto m = glm::mat4();
  m[0][0] = in.a1;
  m[1][0] = in.a2;
  m[2][0] = in.a3;
  m[3][0] = in.a4;

  m[0][1] = in.b1;
  m[1][1] = in.b2;
  m[2][1] = in.b3;
  m[3][1] = in.b4;

  m[0][2] = in.c1;
  m[1][2] = in.c2;
  m[2][2] = in.c3;
  m[3][2] = in.c4;

  m[0][3] = in.d1;
  m[1][3] = in.d2;
  m[2][3] = in.d3;
  m[3][3] = in.d4;

  return m;
}
