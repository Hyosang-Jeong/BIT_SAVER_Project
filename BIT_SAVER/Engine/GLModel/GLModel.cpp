/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GLModel.cpp
Project: BIT_SAVER
Author:	Jaewoo Choi
-----------------------------------------------------------------*/
#include"../Engine.h"
#include"GLModel.h"
#include<iostream>
void glErrorCheck(GLenum err)
{
    if (err != GL_NO_ERROR)
    {
        Engine::GetLogger().LogError("Error in openGL");
       // Engine::GetLogger().LogDebug("Error code is" + std::to_string(static_cast<int>(err)));
       // exit(EXIT_FAILURE);
       // std::cout << gluErrorString(err) << std::endl;
    }
}

GLModel::GLModel()
{
    std::vector<std::pair<GLenum, std::string>> shdr_file0
    {
        std::make_pair(GL_VERTEX_SHADER, "../shaders/Hero.vert"),
        std::make_pair(GL_FRAGMENT_SHADER,  "../shaders/Hero.frag")
    };
    shdr_pgm.CompileLinkValidate(shdr_file0);
    if (GL_FALSE == shdr_pgm.IsLinked())
    {
        std::cout << "Unable to compile/link/validate shader programs\n";
        std::cout << shdr_pgm.GetLog() << "\n";
        std::exit(EXIT_FAILURE);
    }
    init({ 1,1 });
}

void GLModel::init(glm::vec2 size)
{
    // init model from meshes file 
    pos_vtx =
    {
    glm::vec2(-1.0f, -1.0f), glm::vec2(1.f, -1.0f),
    glm::vec2(-1.0f, 1.0f), glm::vec2(1.f, 1.0f)
    };

    idx_vtx =
    {
        2,0,3,1
    };

    text_cord =
    {
        glm::vec2(0.0f, 0.0f), glm::vec2(size.x, 0.0f),
        glm::vec2(0.0f, 1.0f), glm::vec2(size.x, 1.0f)
    };

    vertices.push_back({ pos_vtx[0],text_cord[0] });
    vertices.push_back({ pos_vtx[1],text_cord[1] });
    vertices.push_back({ pos_vtx[2],text_cord[2] });
    vertices.push_back({ pos_vtx[3],text_cord[3] });
    indices.push_back(idx_vtx[0]);
    indices.push_back(idx_vtx[1]);
    indices.push_back(idx_vtx[2]);
    indices.push_back(idx_vtx[3]);

    GLuint vbo_hdl;
    GLuint ebo_hdl;
    glGenVertexArrays(1, &vaoid);
    glErrorCheck(glGetError());
    glGenBuffers(1, &vbo_hdl); 
   // glErrorCheck(glGetError());
    glGenBuffers(1, &ebo_hdl);
   // glErrorCheck(glGetError());
    glBindVertexArray(vaoid);
  //  glErrorCheck(glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, vbo_hdl);
   // glErrorCheck(glGetError());
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
   // glErrorCheck(glGetError());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_hdl);
   // glErrorCheck(glGetError());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);
   // glErrorCheck(glGetError());
    // vertex positions
    glEnableVertexAttribArray(0);
   // glErrorCheck(glGetError());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  //  glErrorCheck(glGetError());
    // vertex texture
    glEnableVertexAttribArray(2);
  //  glErrorCheck(glGetError());
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
  //  glErrorCheck(glGetError());
    primitive_type = GL_TRIANGLE_STRIP;
    draw_cnt = static_cast<GLuint>(idx_vtx.size());
    glBindVertexArray(0);
 //   glErrorCheck(glGetError());
}

void GLModel::update(glm::vec2 min, glm::vec2 frame_size) // todo process memory fix - hyosang 
{
    vertices[0].tex_coord = min;
    vertices[1].tex_coord = { min.x+frame_size.x,min.y };
    vertices[2].tex_coord = { min.x,min.y+frame_size.y };
    vertices[3].tex_coord = { min.x + frame_size.x,min.y + frame_size.y };

    GLuint vbo_hdl;

    glGenBuffers(1, &vbo_hdl);
    glBindVertexArray(vaoid);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_hdl);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));

    primitive_type = GL_TRIANGLE_STRIP;
    draw_cnt = static_cast<GLuint>(idx_vtx.size());
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo_hdl);
}