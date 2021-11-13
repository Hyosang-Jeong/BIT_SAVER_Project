#include"GLModel.h"
#include<iostream>


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

    // vertex texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));


    primitive_type = GL_TRIANGLE_STRIP;
    draw_cnt = static_cast<GLuint>(idx_vtx.size());
    glBindVertexArray(0);
}

void GLModel::Hero_init()
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
        glm::vec2(0.125f, 0.0f), glm::vec2(0.25f, 0.0f),
        glm::vec2(0.125f, 1.0f), glm::vec2(0.25f, 1.0f)
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
    // vertex texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));

    primitive_type = GL_TRIANGLE_STRIP;
    draw_cnt = static_cast<GLuint>(idx_vtx.size());

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