#version 450 core

in vec2 TexCoords;
out vec4 color;

uniform vec3 textColor;
uniform sampler2D text;

void main()
{    
    color = vec4(textColor, texture(text, TexCoords).r);
}