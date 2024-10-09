#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>

namespace GraphicsGorilla
{
  class Window
  {
    GLFWwindow *window;
    std::function<void()> Init;
    std::function<void(int,int)> Draw;
    std::function<void()> Update;

  public:
    Window(int width, int height, const char *title)
    {
      if (!glfwInit())
      {
        return;
      }
      window = glfwCreateWindow(width, height, title, NULL, NULL);
      if (!window)
      {
        glfwTerminate();
        return;
      }
      glfwMakeContextCurrent(window);
      if (glewInit() != GLEW_OK)
      {
        return;
      }
    }

    ~Window()
    {
      glfwDestroyWindow(window);
      glfwTerminate();
    }

    void Run()
    {
      while (!glfwWindowShouldClose(window))
      {
        if (Update)
        {
          Update();
        }
        if (Draw)
        {
          int width, height;
          glfwGetFramebufferSize(window, &width, &height);
          Draw(width, height);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
      }
    }
    void SetDrawFunction(std::function<void(int,int)> draw)
    {
      Draw = draw;
    }

    void SetUpdateFunction(std::function<void()> update)
    {
      Update = update;
    }
  };
}