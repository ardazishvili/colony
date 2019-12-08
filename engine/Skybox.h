#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include <vector>

class Skybox
{
public:
  Skybox();
  void loadCubemap(std::vector<std::string> faces);
  void render();

private:
  unsigned int _vao;
  unsigned int _vbo;
  unsigned int _id;
};

#endif
