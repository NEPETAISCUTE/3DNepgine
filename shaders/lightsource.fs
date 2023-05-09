#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(1.0); //texture(ourTexture, texCoord);
}