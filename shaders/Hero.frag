#version 450 core
layout (location=0) in vec3 vInterpColor;
layout(location=1) in vec2 vTexCoord;

layout (location=0) out vec4 fFragColor;

uniform sampler2D uTex2d;

uniform mat3 textureMatrix;
uniform float alpha;

void main () 
{

     vec3 tex_coord =  textureMatrix * vec3(vTexCoord,1.f);
     vec2 result_coord = vec2(tex_coord.x , tex_coord.y);
    if(alpha ==0)
    {
     fFragColor = texture(uTex2d, result_coord) ;
    
    }
    else
    {
      fFragColor = texture(uTex2d, result_coord) *vec4(1.0,1.0,1.0,alpha) ;  
    }
     
}
