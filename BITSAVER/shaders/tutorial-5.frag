#version 450 core
layout (location=0) in vec3 vInterpColor;
layout(location=1) in vec2 vTexCoord;

layout (location=0) out vec4 fFragColor;

uniform sampler2D uTex2d;

uniform int mode_frag;

uniform int color_frag;

uniform float tile_size;

void main () 
{

   if(mode_frag == 0)
   {
      fFragColor = vec4(vInterpColor.x,vInterpColor.y,vInterpColor.z, 1.0);
   }

  else if(mode_frag <=2 &&  color_frag == 0)
   {
      if(mod(gl_FragCoord.x /tile_size,2)  < 1)
      {
         fFragColor = vec4(1.0,0.0, 1.0, 1.0);
         if(mod(gl_FragCoord.y /tile_size,2)  < 1)
            {
               fFragColor = vec4(0.0, 0.68, 0.94, 1.0);            
            }
      }

      if(mod(gl_FragCoord.x /tile_size,2)  > 1)
      {
           fFragColor = vec4(1.0,0.0, 1.0, 1.0);
            
           if(mod(gl_FragCoord.y /tile_size,2)  > 1)
           {
                 fFragColor = vec4(0.0, 0.68, 0.94, 1.0);            
           }
      }
   }
   

   else if(mode_frag <=2 &&color_frag == 1)
   {
        if(mod(gl_FragCoord.x /tile_size,2)  < 1)
          {        
                fFragColor = vec4(dot(1.0, vInterpColor.x), dot(0.0, vInterpColor.y), dot(1.0, vInterpColor.z), 1.0);   
                if(mod(gl_FragCoord.y /tile_size,2)  < 1)
                {
                    fFragColor = vec4(0.0,0.68, 0.94, 1.0)* vec4(vInterpColor,1.0);
                }
          }
   
         if(mod(gl_FragCoord.x /tile_size,2)  > 1)
         {
            
               fFragColor = vec4(dot(1.0, vInterpColor.x), dot(0.0, vInterpColor.y), dot(1.0, vInterpColor.z), 1.0);
                  if(mod(gl_FragCoord.y /tile_size,2)  > 1)
                 {
                   fFragColor = vec4(0.0, 0.68,0.94, 1.0) * vec4(vInterpColor,1.0);
                  }
         }
     }
     else if(mode_frag >= 3 && color_frag == 0)
     {
            fFragColor = texture(uTex2d, vTexCoord);
     }
     else if(mode_frag >= 3 && color_frag ==1)
     {
           fFragColor = texture(uTex2d, vTexCoord) * vec4(vInterpColor,1.0);
     }
   
}
