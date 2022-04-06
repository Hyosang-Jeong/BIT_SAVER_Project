/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.h
Project: BIT_SAVER
Author: Sunwoo Lee
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include<Windows.h>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
class Serial;
class Window
{
public:
    void Init(GLint wid, GLint hei, std::string windowName);
    void Update();
    void Resize(int newWidth, int newHeight);
    glm::vec2 GetSize();

    static void fbsize_cb(GLFWwindow* ptr_win, int width, int height);
    // I/O callbacks ...
    static void key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod);
    static void mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod);
    static void mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset);
    static void mousepos_cb(GLFWwindow* pwin, double xpos, double ypos);
    GLFWwindow* ptr_window;
private:
    GLint width, height;
    std::string title;
    glm::vec2 windowSize;

    //for arduino
    Serial* SP;
    char incomingData[256] = "";
};
