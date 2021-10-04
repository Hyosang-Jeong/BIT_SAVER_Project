/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Project: CS230
Author: Hyosang Jung
Creation date: 3/13/2021
-----------------------------------------------------------------*/

#include "Window.h"
#include"Input.h"
#include "Engine.h"			// GetWindow
void Window::Init(GLint wid, GLint hei,std::string windowName)
{
    Window::width = wid;
    Window::height = hei;
    Window::title = windowName;
    if (!glfwInit()) 
    {
        std::cout << "GLFW init has failed - abort program!!!" << std::endl; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static

   ptr_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

   glfwMakeContextCurrent(ptr_window);

   glfwSetFramebufferSizeCallback(ptr_window, fbsize_cb);
   glfwSetKeyCallback(ptr_window, key_cb);
  // glfwSetMouseButtonCallback(ptr_window,mousebutton_cb);
//   glfwSetCursorPosCallback(ptr_window, mousepos_cb);
 //  glfwSetScrollCallback(ptr_window, mousescroll_cb);

   // this is the default setting ...
   glfwSetInputMode(ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

   // Part 2: Initialize entry points to OpenGL functions and extensions
   GLenum err = glewInit();

   if (GLEW_OK != err) 
   {
       std::cerr << "Unable to initialize GLEW - error: ";
       //    << glewGetErrorString(err) << " abort program" << std::endl;
       //return false;
   }
   if (GLEW_VERSION_4_5) {
       std::cout << "Using glew version: " << glewGetString(GLEW_VERSION) << std::endl;
       std::cout << "Driver supports OpenGL 4.5\n" << std::endl;
   }
   else 
   {
       std::cerr << "Driver doesn't support OpenGL 4.5 - abort program" << std::endl;
       //return false;
   }
   //return true;
}
void Window::Update() 
{
    glfwPollEvents();
}

void on_window_resized(int new_width, int new_height)
{
    Engine::GetLogger().LogEvent("Window Resized");
    Engine::GetWindow().Resize(new_width, new_height);
}
void Window::Resize(int newWidth, int newHeight)
{
    windowSize = { newWidth,newHeight };
}

math::ivec2 Window::GetSize()
{
    return windowSize;
}

//void Window::Clear(unsigned int color)
//{
//    doodle::clear_background(doodle::HexColor{ color });
//}

InputKey::Keyboard GLKEY_TO_GAME(int button)
{
    if (button == GLFW_KEY_ENTER) {
        return InputKey::Keyboard::Enter;
    }
    else if (button == GLFW_KEY_ESCAPE) {
        return InputKey::Keyboard::Escape;
    }
    else if (button == GLFW_KEY_SPACE) {
        return InputKey::Keyboard::Space;
    }
    else if (button == GLFW_KEY_LEFT) {
        return InputKey::Keyboard::Left;
    }
    else if (button == GLFW_KEY_RIGHT) {
        return InputKey::Keyboard::Right;
    }
    else if (button == GLFW_KEY_UP) {
        return InputKey::Keyboard::Up;
    }
    else if (button == GLFW_KEY_DOWN) {
        return InputKey::Keyboard::Down;
    }

    else if (button >= GLFW_KEY_A && button <= GLFW_KEY_Z) {
        int offset = static_cast<int>(button) - static_cast<int>(GLFW_KEY_A);
        return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
    }
    return InputKey::Keyboard::None;
}



void Window::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod)
{
    if (GLFW_PRESS == action)
    {
        InputKey::Keyboard button = GLKEY_TO_GAME(key);
        if (button != InputKey::Keyboard::None)
        {
            Engine::GetLogger().LogDebug("on_key_pressed");
            Engine::GetInput().SetKeyDown(button, true);
        }
    }
    else if (GLFW_REPEAT == action)
    {
#ifdef _DEBUG
        Engine::GetLogger().LogDebug("Key repeated");
#endif
    }
    else if (GLFW_RELEASE == action)
    {
        InputKey::Keyboard button = GLKEY_TO_GAME(key);
        if (button != InputKey::Keyboard::None)
        {
            Engine::GetLogger().LogDebug("on_key_released");
            Engine::GetInput().SetKeyDown(button, false);
        }

    }

    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(pwin, GLFW_TRUE);
    }

}

void Window::mousebutton_cb(GLFWwindow* pwin, int button, int action, int mod)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
        std::cout << "Left mouse button ";
#endif
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
        std::cout << "Right mouse button ";
#endif
        break;
    }
    switch (action)
    {
    case GLFW_PRESS:
#ifdef _DEBUG
        std::cout << "pressed!!!" << std::endl;
#endif
        break;
    case GLFW_RELEASE:
#ifdef _DEBUG
        std::cout << "released!!!" << std::endl;
#endif
        break;
    }
}


void Window::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos)
{

}


void Window::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
    std::cout << "fbsize_cb getting called!!!" << std::endl;
    // use the entire framebuffer as drawing region
    glViewport(0, 0, width, height);
    // later, if working in 3D, we'll have to set the projection matrix here ...
}