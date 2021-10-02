/*!
@file    glapp.cpp
@author  pghali@digipen.edu, hyosang jung
@date    10/11/2016

This file implements functionality useful and necessary to build OpenGL
applications including use of external APIs such as GLFW to create a
window and start up an OpenGL context and to extract function pointers
to OpenGL implementations.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "glapp.h"
#include "glhelper.h"
#include<array> // for array
#include<cstdlib> // for random number
#include <fstream>
/*                                                   objects with file scope
----------------------------------------------------------------------------- */
static GLApp    g_glapp;
GLApp::GLModel GLApp::mdl;
static int mode_frag = 0;
void GLApp::init()  // add opengl info code by hyosang jung
{
    // Part 1: clear colorbuffer with RGBA value in glClearColor ...
    glClearColor(1.f, 1.f, 1.f, 1.f);
    // Part 2: use the entire window as viewport ...
    GLint w = GLHelper::width, h = GLHelper::height;
    glViewport(0, 0, w, h);
    // Part 3: initialize VAO and create shader program
    mdl.setup_vao();
    mdl.setup_shdrpgm();
}

void GLApp::update(double delta_time)  // add random color logic by hyosang jung
{
    constexpr float PI = 3.14159265358979323846f;
    static float tile_size = 32;
    static bool is_released = false;
    mdl.shdr_pgm.Use();
    GLint uniform_var_loc1 = glGetUniformLocation(mdl.shdr_pgm.GetHandle(), "mode_frag");
    GLint uniform_var_loc2 = glGetUniformLocation(mdl.shdr_pgm.GetHandle(), "tile_size");

    static double timer = 0;
    static bool increasing = true;

    if ( increasing ==true)
    {
        timer += delta_time;
    }
    else if (increasing == false)
    {
        timer -= delta_time;
    }

    if (timer >= 30)
    {
        increasing = false;
    }
    if (timer < 0)
    {
        increasing = true;
    }

    double t = timer / 30.0;
    double e = (sin((PI * t) - (PI / 2.0)) + 1 )/ 2.0;
    if (mode_frag == 2)
    {
        tile_size = 16 + static_cast<float>(e * (240));
    }
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_T) == GLFW_RELEASE)
    {
        is_released = true;
    }

    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_T) == GLFW_PRESS && is_released == true)
    {
        mode_frag++;
        if (mode_frag == 2)
        {
            timer = 0;
        }
        if (mode_frag == 7)
        {
            mode_frag = 0;
        }
        is_released = false;
    }

    if (uniform_var_loc1 >= 0)
    {
        glUniform1i(uniform_var_loc1, mode_frag);
    }

    if (uniform_var_loc2 >= 0 )
    {
            glUniform1f(uniform_var_loc2, tile_size);
    }

}

void GLApp::draw()
{
    // clear back buffer as before
    glClear(GL_COLOR_BUFFER_BIT);
    // now, render rectangular model from NDC coordinates to viewport
    mdl.draw();
}
GLuint setup_texobj(std::string pathname)
{
    GLuint width{ 256 }, height{ 256 }, bytes_per_texel{ 4 };
    GLuint texobj_hdl;
    char* ptr_texels = nullptr;
    std::ifstream is(pathname, std::ifstream::binary);
    if (is)
    {
        int length = width * height * bytes_per_texel;
        ptr_texels = new char[length];
        is.read(ptr_texels, length);
        is.close();
    }
    glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
    // allocate GPU storage for texture image data loaded from file
    glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
        GL_RGBA, GL_UNSIGNED_BYTE, ptr_texels);

    // client memory not required since image is buffered in GPU memory
    delete[] ptr_texels;
    // nothing more to do - return handle to texture object
    return texobj_hdl;
}
void GLApp::GLModel::draw()
{
    static bool is_Mreleased = true;
    static bool is_Areleased = true;
    static int color_frag = 0;
    static bool is_opaque = true;
    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_M) == GLFW_RELEASE)
    {
        is_Mreleased = true;
    }

    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_M) == GLFW_PRESS && is_Mreleased == true)
    {
        color_frag++;
        if (color_frag == 2)
        {
            color_frag = 0;
        }
        is_Mreleased = false;
    }

    glBindVertexArray(vaoid);

    GLint uniform_var_loc1 = glGetUniformLocation(shdr_pgm.GetHandle(), "color_frag");

    if (uniform_var_loc1 >= 0)
    {
        glUniform1i(uniform_var_loc1, color_frag);
    }

    GLuint  texobj_hdl0 = setup_texobj("../images/duck-rgba-256.tex");
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        is_Areleased = true;
    }

    if (glfwGetKey(GLHelper::ptr_window, GLFW_KEY_A) == GLFW_PRESS && is_Areleased == true)
    {
        if (is_opaque == true)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            is_opaque = false;
        }
        else
        {
            glBlendFunc(GL_ONE, GL_ZERO);
            is_opaque = true;
        }
        is_Areleased = false;
    }

    glBindTexture(GL_TEXTURE_2D, texobj_hdl0);
     glBindTextureUnit(0, texobj_hdl0);
     if (mode_frag == 4)
     {
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_T, GL_REPEAT);
     }
     if (mode_frag == 5)
     {
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
      }
     if (mode_frag == 6)
     {
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTextureParameteri(texobj_hdl0, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     }
    GLuint tex_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uTex2d");
    glUniform1i(tex_loc, 0);

    glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);


    glBindVertexArray(0);
    shdr_pgm.UnUse();

    

}

void GLApp::cleanup() {
    // empty for now
}

void GLApp::GLModel::setup_shdrpgm()
{
    std::vector<std::pair<GLenum, std::string>> shdr_files;
    shdr_files.push_back(std::make_pair(
        GL_VERTEX_SHADER,
        "../shaders/tutorial-5.vert"));
    shdr_files.push_back(std::make_pair(
        GL_FRAGMENT_SHADER,
        "../shaders/tutorial-5.frag"));
    shdr_pgm.CompileLinkValidate(shdr_files);
    if (GL_FALSE == shdr_pgm.IsLinked())
    {
        std::cout << "Unable to compile/link/validate shader programs" << "\n";
        std::cout << shdr_pgm.GetLog() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void GLApp::GLModel::setup_vao()
{
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
    std::vector<GLshort > indices;

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
    idx_elem_cnt = static_cast<GLuint>(idx_vtx.size());
    glBindVertexArray(0);

 }

