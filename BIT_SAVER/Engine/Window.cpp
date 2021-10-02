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
   glfwSetMouseButtonCallback(ptr_window,mousebutton_cb);
   glfwSetCursorPosCallback(ptr_window, mousepos_cb);
   glfwSetScrollCallback(ptr_window, mousescroll_cb);

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

void Window::key_cb(GLFWwindow* pwin, int key, int scancode, int action, int mod)
{
    if (GLFW_PRESS == action)
    {
#ifdef _DEBUG
        std::cout << "Key pressed" << std::endl;
#endif
    }
    else if (GLFW_REPEAT == action)
    {
#ifdef _DEBUG
        std::cout << "Key repeatedly pressed" << std::endl;
#endif
    }
    else if (GLFW_RELEASE == action)
    {
#ifdef _DEBUG
        std::cout << "Key released" << std::endl;
#endif
    }

    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(pwin, GLFW_TRUE);
    }

}

/*  _________________________________________________________________________*/
/*! mousebutton_cb

@param GLFWwindow*
Handle to window that is receiving event

@param int
the mouse button that was pressed or released
GLFW_MOUSE_BUTTON_LEFT and GLFW_MOUSE_BUTTON_RIGHT specifying left and right
mouse buttons are most useful

@parm int
action is either GLFW_PRESS or GLFW_RELEASE

@parm int
bit-field describing which modifier keys (shift, alt, control)
were held down

@return none

This function is called when mouse buttons are pressed.
*/
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

/*  _________________________________________________________________________*/
/*! mousepos_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
new cursor x-coordinate, relative to the left edge of the client area

@param double
new cursor y-coordinate, relative to the top edge of the client area

@return none

This functions receives the cursor position, measured in screen coordinates but
relative to the top-left corner of the window client area.
*/
void Window::mousepos_cb(GLFWwindow* pwin, double xpos, double ypos) {
#ifdef _DEBUG
    std::cout << "Mouse cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________*/
/*! mousescroll_cb

@param GLFWwindow*
Handle to window that is receiving event

@param double
Scroll offset along X-axis

@param double
Scroll offset along Y-axis

@return none

This function is called when the user scrolls, whether with a mouse wheel or
touchpad gesture. Although the function receives 2D scroll offsets, a simple
mouse scroll wheel, being vertical, provides offsets only along the Y-axis.
*/
void Window::mousescroll_cb(GLFWwindow* pwin, double xoffset, double yoffset) {
#ifdef _DEBUG
    std::cout << "Mouse scroll wheel offset: ("
        << xoffset << ", " << yoffset << ")" << std::endl;
#endif
}

/*  _________________________________________________________________________ */
/*! error_cb

@param int
GLFW error code

@parm char const*
Human-readable description of the code

@return none

The error callback receives a human-readable description of the error and
(when possible) its cause.
*/
//void Window::error_cb(int error, char const* description) {
//    std::cerr << "GLFW error: " << description << std::endl;
//}

/*  _________________________________________________________________________ */
/*! fbsize_cb

@param GLFWwindow*
Handle to window that is being resized

@parm int
Width in pixels of new window size

@parm int
Height in pixels of new window size

@return none

This function is called when the window is resized - it receives the new size
of the window in pixels.
*/
void Window::fbsize_cb(GLFWwindow* ptr_win, int width, int height) {
    std::cout << "fbsize_cb getting called!!!" << std::endl;
    // use the entire framebuffer as drawing region
    glViewport(0, 0, width, height);
    // later, if working in 3D, we'll have to set the projection matrix here ...
}