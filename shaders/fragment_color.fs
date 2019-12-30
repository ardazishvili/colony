#version 330 core

flat in vec4 normals_colour;


out vec4 FragColor;

void main()
{
  vec3 rgb = normals_colour.xyz;
  float alpha = normals_colour.w;
  FragColor = vec4(rgb, alpha);
}
