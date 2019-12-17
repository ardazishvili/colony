#version 330 core
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

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
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

  float alfa = texture(material.diffuse, texCoords).w;
  FragColor = vec4(ambient + diffuse + specular, alfa);
  /* FragColor = texture(material.diffuse, texCoords); */
}
