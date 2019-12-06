#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normals;

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


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

flat out vec3 normals_colour;

vec3 calculateLighting() {
  vec3 fragPos = vec3(model * vec4(position, 1.0));
  vec3 normal = mat3(transpose(inverse(model))) * normals;
  vec3 c = color;

  vec3 ambient = light.ambient * c;

  vec3 norm = normalize(normal);
  vec3 lightDirection = normalize(light.position - fragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * light.diffuse * c;

  // vec3 viewDirection = normalize(viewPos - fragPos);
  // vec3 reflectDirection = reflect(-lightDirection, norm);
  // float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 
	// 	   material.shininess);
  // vec3 specular = spec * light.specular * c;

  // return ambient + diffuse + specular;
  return ambient + diffuse;
}

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  normals_colour = calculateLighting();
}
