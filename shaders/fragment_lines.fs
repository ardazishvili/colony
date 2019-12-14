#version 330 core

out vec4 FragColor;
uniform vec2 resolution;

void main() {

  vec2 uv = ( gl_FragCoord.xy / resolution.xy );
	uv *= 2.0;
	uv -= 1.0;
  vec3 color = vec3(1.0f, 0.5f, 0.2f);

  vec2 borderSize = vec2(0.8); 
  vec2 rectangleSize = vec2(1.0) - borderSize; 
  float distanceField = length(max(abs(uv)-rectangleSize,0.0) / borderSize);
  float alfa = 1.0 - distanceField;
  // float alfa = 1.0;

	// color *= abs(0.05 / (sin( uv.x ) * 20.0) );
	// color *=  abs(0.05 / sin(uv.x) * 2 );

  FragColor = vec4(color, alfa);
}

