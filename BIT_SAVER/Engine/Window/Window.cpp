/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Project: BIT_SAVER
Author: Sunwoo Lee
-----------------------------------------------------------------*/
#include "Window.h"
#include"..\Input\Input.h"
#include "..\Engine.h"			// GetWindow
#include"SerialClass.h"
void Window::Init(GLint wid, GLint hei, std::string windowName)
{
    Window::width = wid;
    Window::height = hei;
    Window::title = windowName;
    windowSize = { width,height };
    //Setup arduino
    SP = new Serial("\\\\.\\COM4");


    if (!glfwInit())
    {
        Engine::GetLogger().LogError("GLFW init has failed - abort program!!!");
        std::exit(EXIT_FAILURE);
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // window dimensions are static
    ptr_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    glfwMakeContextCurrent(ptr_window);


    glfwSetFramebufferSizeCallback(ptr_window, fbsize_cb);
    glfwSetKeyCallback(ptr_window, key_cb);
    glfwSetMouseButtonCallback(ptr_window, mousebutton_cb);
    glfwSetCursorPosCallback(ptr_window, mousepos_cb);

    // this is the default setting ...
    glfwSetInputMode(ptr_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    GLenum err = glewInit();

    
    if (GLEW_OK != err)
    {
        Engine::GetLogger().LogError("Unable to initialize GLEW - error: ");
    }
    if (!GLEW_VERSION_4_5)
    {
        Engine::GetLogger().LogError("Driver doesn't support OpenGL 4.5 - abort program");
    }
}
void Window::Update()
{
    int dataLength = 255;
    int readResult = 0;

    readResult = SP->ReadData(incomingData, dataLength);

    incomingData[readResult] = 0;

    if (*incomingData == 'U' )
    {
        Engine::GetLogger().LogDebug("Arduino Up");
        Engine::GetInput().SetKeyDown(Engine::GetAttack_Key().UpAttackKey.button, true);
      //  Engine::GetInput().SetKeyDown(InputKey::Keyboard::Up, true);
       //Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::Up);
    }
    else if (*incomingData == 'D')
    {
        Engine::GetLogger().LogDebug("Arduino Down");
        Engine::GetInput().SetKeyDown(Engine::GetAttack_Key().DownAttackKey.button, true);
      //  Engine::GetInput().SetKeyDown(InputKey::Keyboard::Down, true);
       // Engine::GetInput().SetLastpressedButton(InputKey::Keyboard::Down);
    }
    else if (*incomingData == 'N')
    {
        Engine::GetInput().SetKeyDown(Engine::GetAttack_Key().UpAttackKey.button, false);
        Engine::GetInput().SetKeyDown(Engine::GetAttack_Key().DownAttackKey.button, false);
    }
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

glm::vec2 Window::GetSize()
{
    return windowSize;
}

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
    else if (button == GLFW_KEY_DOWN)
    {
        return InputKey::Keyboard::Down;
    }
    else if (button == GLFW_KEY_0)
    {
        return InputKey::Keyboard::NUM_0;
    }
    else if (button == GLFW_KEY_1)
    {
        return InputKey::Keyboard::NUM_1;
    }
    else if (button == GLFW_KEY_2)
    {
        return InputKey::Keyboard::NUM_2;
    }
    else if (button == GLFW_KEY_3)
    {
        return InputKey::Keyboard::NUM_3;
    }
    else if (button == GLFW_KEY_GRAVE_ACCENT)
    {
        return InputKey::Keyboard::Tilde;
    }
    else if (button >= GLFW_KEY_A && button <= GLFW_KEY_Z)
    {
        int offset = static_cast<int>(button) - static_cast<int>(GLFW_KEY_A);
        return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
    }
    return InputKey::Keyboard::None;
}

InputKey::Mouse GLMOUSEKEY_TO_GAME(int button)
{
    if (button == GLFW_KEY_ENTER) {
        return InputKey::Mouse::None;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT) {
        return InputKey::Mouse::Left;
    }
    return InputKey::Mouse::None;
}

void Window::key_cb([[maybe_unused]] GLFWwindow* pwin, [[maybe_unused]] int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mod)
{
    if (GLFW_PRESS == action)
    {
        InputKey::Keyboard button = GLKEY_TO_GAME(key);
        if (button != InputKey::Keyboard::None)
        {
            Engine::GetLogger().LogDebug("on_key_pressed");
            Engine::GetInput().SetKeyDown(button, true);
            Engine::GetInput().SetLastpressedButton(button);
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


}

void Window::mousebutton_cb([[maybe_unused]] GLFWwindow* pwin, int button, int action, [[maybe_unused]] int mod)
{
    InputKey::Mouse key;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
        Engine::GetLogger().LogDebug("Left mouse button ");

#endif
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
        Engine::GetLogger().LogDebug("Right mouse button ");
#endif
        break;
    }
    switch (action)
    {
    case GLFW_PRESS:
        key = GLMOUSEKEY_TO_GAME(button);
        Engine::GetInput().MouseSetKeyDown(key, true);
#ifdef _DEBUG
        Engine::GetLogger().LogDebug("pressed! ");

#endif
        break;
    case GLFW_RELEASE:
        key = GLMOUSEKEY_TO_GAME(button);
        Engine::GetInput().MouseSetKeyDown(key, false);
#ifdef _DEBUG
        Engine::GetLogger().LogDebug("released! ");
#endif
        break;
    }
}


void Window::mousepos_cb([[maybe_unused]] GLFWwindow* pwin, [[maybe_unused]] double xpos, [[maybe_unused]] double ypos)
{
    Engine::GetInput().MouseSetPosition({ xpos,ypos });
#ifdef _DEBUG

#endif

}


void Window::fbsize_cb([[maybe_unused]] GLFWwindow* ptr_win, int width, int height)
{
    glViewport(0, 0, width, height);
}