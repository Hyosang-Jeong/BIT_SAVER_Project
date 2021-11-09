#include"Collision.h"
#include "..\Engine.h"

Render::Render(void)
{
    GLint value;
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_text =
        "#version 130\n\
     uniform vec3 color;\
     out vec4 frag_color;\
     void main(void) {\
       frag_color = vec4(color,1);\
     }";
    glShaderSource(fshader, 1, &fragment_shader_text, 0);
    glCompileShader(fshader);
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);


    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader_text =
        "#version 130\n\
     attribute vec4 position;\
     void main() {\
       gl_Position = position;\
     }";
    glShaderSource(vshader, 1, &vertex_shader_text, 0);
    glCompileShader(vshader);
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);


    program = glCreateProgram();
    glAttachShader(program, fshader);
    glAttachShader(program, vshader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &value);

    ucolor = glGetUniformLocation(program, "color");
    aposition = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(aposition);

   // glEnable(GL_DEPTH_TEST);
}

void Render::SetColor(glm::vec3 c)
 {
    glUseProgram(program);
    glUniform3f(ucolor, c[0], c[1], c[2]);
}



void Render::DrawLine(glm::vec2 P, glm::vec2 Q )
{
    glUseProgram(program);
    glLineWidth(10);
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    float vertices[8] = { P.x/10.f,P.y/10.f,0,1, Q.x/10.f,Q.y/10.f,0,1 };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(aposition, 4, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, 2);
    glDeleteBuffers(1, &vertex_buffer);
}


Collision::Collision(glm::vec2 size) :box_size(size) 
{}

const AABB& Collision::GetAABB() const
{
    return collision_box;
}

void Collision::UpdateCollision(glm::vec2 pos,glm::vec2 scale)
{
    collision_box.min = { pos.x - (scale.x  / 2.f), pos.y - (scale.y/ 2.f) };
    collision_box.max = { pos.x + (scale.x/ 2.f), pos.y + (scale.y / 2.f) };
}

void Collision::Draw()
{
    // for draw collision box - not complete
   /* glm::vec3 color(0.f, 0.f, 1.f);
    render.SetColor(color);
    render.DrawLine(collision_box.min, collision_box.max);*/
}