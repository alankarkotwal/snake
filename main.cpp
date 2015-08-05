//
//  main.cpp
//  
//
//  Created by Alankar Kotwal on 06/08/15.
//
//

#include <iostream>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "snake.h"

#define GLFW_FRAME_INTERVAL 0.1
#define SNAKE_SCALE 0.001

snake_t mySnake;
GLuint shaderProgram;
GLuint vbo, vao;

void updateCallback() {
    
    std::queue<vertex> snakeQueue = mySnake.getSnake();
    /*while(!snakeQueue.empty()) {
        vertex myVertex = snakeQueue.front();
        snakeQueue.pop();
        std::cout << (float)myVertex.x/1000 << "\t" << (float)myVertex.y/1000 << std::endl;
    }
    std::cout << "***" << std::endl;*/
    
    // Render snake
    float points[18*snakeQueue.size()];
    int i = 0;
    while(!snakeQueue.empty()) {
        vertex myVertex = snakeQueue.front();
        snakeQueue.pop();
        points[i] = ((float)myVertex.x-0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y+0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
        points[i] = ((float)myVertex.x-0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y-0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
        points[i] = ((float)myVertex.x+0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y+0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
        points[i] = ((float)myVertex.x-0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y-0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
        points[i] = ((float)myVertex.x+0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y+0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
        points[i] = ((float)myVertex.x+0.5)/SNAKE_SCALE; i++;
        points[i] = ((float)myVertex.y-0.5)/SNAKE_SCALE; i++;
        points[i] = 1.0; i++;
    }
    
    
    // Update snake
    mySnake.updateSnake();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        mySnake.setDir(SNAKE_DOWN);
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        mySnake.setDir(SNAKE_UP);
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        mySnake.setDir(SNAKE_LEFT);
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        mySnake.setDir(SNAKE_RIGHT);
    }
}

void initShadersGL(void) {
    
    std::string vertex_shader_file("simple_vs.glsl");
    std::string fragment_shader_file("simple_fs.glsl");
    
    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));
    
    shaderProgram = csX75::CreateProgramGL(shaderList);
}

int main() {
    
    GLFWwindow* window;
    
    if(!glfwInit())
        exit(0);
    
    //We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "SNAKE", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    //! Make the window's context current
    glfwMakeContextCurrent(window);
    
    //Initialize GLEW
    //Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        //Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW Init Failed : %s" << std::endl;
    }
    
    //Keyboard Callback
    glfwSetKeyCallback(window, keyCallback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    //Initialize GL state
    csX75::initGL();
    initShadersGL();
    
    while (glfwWindowShouldClose(window) == 0) {
        
        std::cout << "Loop" << std::endl;
        double loopStart = glfwGetTime();
        updateCallback();
        glfwPollEvents();
        while(glfwGetTime()-loopStart < GLFW_FRAME_INTERVAL);
    }
    
    glfwTerminate();
    return 0;
}

