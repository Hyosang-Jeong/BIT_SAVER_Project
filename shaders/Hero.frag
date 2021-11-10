#version 450 core
layout (location=0) in vec3 vInterpColor;
layout(location=1) in vec2 vTexCoord;

layout (location=0) out vec4 fFragColor;

uniform sampler2D uTex2d;

void main () 
{
           fFragColor = texture(uTex2d, vTexCoord) ;  
}
