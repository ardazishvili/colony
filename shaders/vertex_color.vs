#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
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
uniform bool flatView;

flat out vec4 normals_colour;
out vec3 worldPos;
out vec3 lightAmbient;

vec3 calculateLighting() {
  vec3 fragPos = vec3(model * vec4(position, 1.0));
  vec3 normal = mat3(transpose(inverse(model))) * normals;
  vec3 c = color.xyz;

  vec3 ambient = light.ambient * c;

  vec3 norm = normalize(normal);
  vec3 lightDirection = normalize(light.position - fragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * light.diffuse * c;

  return ambient + diffuse;
}

void main()
{
  if (!flatView) {
    // Gall
    float R = 4.0 * 3.1415;
    float S = 6.0 * 3.1415;
    float longitude = position.x * sqrt(2.0f) / R;
    float latitude = 2 * atan(position.y / (R * (1 + sqrt(2) / 2.0f)));

    vec3 p;
    p.x = (S + position.z) * cos(latitude) * cos(longitude);
    p.y = (S + position.z) * cos(latitude) * sin(longitude);
    p.z = (S + position.z) * sin(latitude);
    gl_Position = projection * view * model * vec4(p, 1.0);
  } else {
    gl_Position = projection * view * model * vec4(position, 1.0);
  }

  vec4 wp = model * vec4(position, 1.0);
  worldPos = wp.xyz;

  normals_colour = vec4(calculateLighting(), color.w);
  lightAmbient = light.ambient;
}
