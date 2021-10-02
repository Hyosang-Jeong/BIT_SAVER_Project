#include"GLModel.h"
#include<array>
#include<iostream>
#include<vector>
void GLModel::set_name(std::string model_name)
{
    //Author: Hyosang Jung
   //Set model's name
    name = model_name;
}

void GLModel::init() //now for hero only
{
    // author: Hyosang Jung
   // init model from meshes file 
    std::array<glm::vec2, 4> pos_vtx
    {
    glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, -1.0f),
    glm::vec2(-1.0f, 1.0f), glm::vec2(1.0f, 1.0f)
    };

    std::array<glm::vec3, 4> clr_vtx{
    glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
    };

    std::array<GLushort, 4> idx_vtx
    {
        2,0,3,1
    };

    std::array<glm::vec2, 4>text_cord
    {
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f)
    };

    std::vector<Vertex> vertices;
    std::vector<GLshort> indices;

    vertices.push_back({ pos_vtx[0],clr_vtx[0],text_cord[0] });
    vertices.push_back({ pos_vtx[1],clr_vtx[1],text_cord[1] });
    vertices.push_back({ pos_vtx[2],clr_vtx[2],text_cord[2] });
    vertices.push_back({ pos_vtx[3],clr_vtx[3],text_cord[3] });
    indices.push_back(idx_vtx[0]);
    indices.push_back(idx_vtx[1]);
    indices.push_back(idx_vtx[2]);
    indices.push_back(idx_vtx[3]);

    GLuint vbo_hdl;
    GLuint ebo_hdl;
    glGenVertexArrays(1, &vaoid);
    glGenBuffers(1, &vbo_hdl);
    glGenBuffers(1, &ebo_hdl);

    glBindVertexArray(vaoid);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_hdl);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_hdl);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // vertex texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));


    primitive_type = GL_TRIANGLE_STRIP;
    draw_cnt = static_cast<GLuint>(idx_vtx.size());
    glBindVertexArray(0);
}
