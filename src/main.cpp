#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "components/MeshComponent.h"
#include "graphics/AssetManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Camera.h"
#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "nodes/GameManager.h"
#include "nodes/SpinningCube.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

Scene scene;

const u_int SCR_WIDTH = 960;
const u_int SCR_HEIGHT = 660;

const u_int FRAME_WIDTH = 320;
const u_int FRAME_HEIGHT = 220;

int winW = SCR_WIDTH;
int winH = SCR_HEIGHT;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct Viewport {
  int x, y, w, h;
};

bool integerScaling = true;

Viewport letterbox(int winW, int winH, int frameW, int frameH) {
  if (integerScaling) {
    int scale = max(1, min(winW / frameW, winH / frameH));
    int w = frameW * scale;
    int h = frameH * scale;
    return {(winW - w) / 2, (winH - h) / 2, w, h};
  } else {
    float aspect = (float)frameW / (float)frameH;
    int w = winW, h = (int)(winW / aspect);
    if (h > winH) {
      h = winH;
      w = (int)(winH * aspect);
    }
    return {(winW - w) / 2, (winH - h) / 2, w, h};
  }
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  u_int fbo, fboTex, fboDepth;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &fboTex);
  glBindTexture(GL_TEXTURE_2D, fboTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FRAME_WIDTH, FRAME_HEIGHT, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         fboTex, 0);

  glGenRenderbuffers(1, &fboDepth);
  glBindRenderbuffer(GL_RENDERBUFFER, fboDepth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FRAME_WIDTH,
                        FRAME_HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, fboDepth);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Framebuffer incomplete!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  Shader blitShader;
  blitShader.Init("assets/shaders/blit_v.glsl", "assets/shaders/blit_f.glsl");

  u_int blitVAO;
  glGenVertexArrays(1, &blitVAO);

  AssetManager::Init(&scene.camera, (float)FRAME_WIDTH, (float)FRAME_HEIGHT);
  scene.root->AddChild(make_shared<GameManager>());

  // ===[ Render Loop ]===
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    scene.Update(deltaTime, window);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    AssetManager::Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto [x, y, w, h] = letterbox(winW, winH, FRAME_WIDTH, FRAME_HEIGHT);
    glViewport(x, y, w, h);

    blitShader.Use();
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glBindVertexArray(blitVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  winW = width;
  winH = height;
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  scene.camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  scene.camera.ProcessMouseScroll(static_cast<float>(yoffset));
}