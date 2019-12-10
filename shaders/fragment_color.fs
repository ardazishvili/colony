#version 330 core

flat in vec3 normals_colour;

out vec4 FragColor;

void main()
{
  FragColor = vec4(normals_colour, 0.3);
}
