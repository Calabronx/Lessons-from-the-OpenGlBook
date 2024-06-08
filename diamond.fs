#version 330 core
out vec4 FragColor;
in vec3 pyramidColor;

void main()
{
  FragColor = vec4(pyramidColor, 1.0f);
}