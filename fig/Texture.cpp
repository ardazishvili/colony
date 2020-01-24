#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(GLenum textureType, const std::string& filename)
{
  _textureType = textureType;
  _filename = filename;
}

Texture::~Texture()
{
  glDeleteTextures(1, &_id);
}

bool Texture::load()
{
  int width, height, nrComponents;
  unsigned char* data =
    stbi_load(_filename.c_str(), &width, &height, &nrComponents, 0);

  if (data) {

    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;
    glGenTextures(1, &_id);
    glBindTexture(_textureType, _id);
    glTexImage2D(_textureType,
                 0,
                 format,
                 width,
                 height,
                 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 data);
    glTexParameterf(_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    glBindTexture(_textureType, 0);
  } else {
    std::cout << "Texture failed to load : " << _filename << std::endl;
    stbi_image_free(data);
    return false;
  }

  _loaded = true;
  return true;
}

void Texture::bind(GLenum textureType)
{
  glActiveTexture(textureType);
  glBindTexture(_textureType, _id);
}

bool Texture::loaded() const
{
  return _loaded;
}

GLuint Texture::getTextureId() const
{
  return _id;
}
