#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>

class Texture
{
public:
    Texture(GLenum textureType, const std::string& filename);
    ~Texture();
    bool load();
    void bind(GLenum textureType);
    bool loaded() const;
    GLuint getTextureId() const;

private:
    std::string _filename;
    GLenum _textureType;
    GLuint _id;
    bool _loaded { false };
};


#endif	/* TEXTURE_H */

