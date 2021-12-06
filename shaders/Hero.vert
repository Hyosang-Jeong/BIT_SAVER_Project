#version 450 core

layout (location=0) in vec2 aVertexPosition;

layout (location=2) in vec2 aTexCoord;

uniform mat3 uModelToNDC;
layout (location=0) out vec3 vColor;
layout (location=1) out vec2 vTex;

void main()
{
   gl_Position = vec4(vec2(uModelToNDC * vec3(aVertexPosition, 1.f)), 0.0,
1.0);
	vTex = aTexCoord ;
}
