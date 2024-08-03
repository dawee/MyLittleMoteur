// Your First C++ Program

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"


Camera camera;
bool firstMouse = true;
float lastX;
float lastY;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f,
};

float debugVertices[36 * 3 * 2];

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera.ProcessInput(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void setupDebugNormals()
{
    for (int i = 0; i < 36; i++)
    {
        auto indice = i * 8;
        auto indiceDebug = i * 6;
        debugVertices[indiceDebug + 0] = vertices[indice];
        debugVertices[indiceDebug + 1] = vertices[indice] + vertices[indice + 5];
        debugVertices[indiceDebug + 2] = vertices[indice + 1];
        debugVertices[indiceDebug + 3] = vertices[indice + 1] + vertices[indice + 6];
        debugVertices[indiceDebug + 4] = vertices[indice + 2];
        debugVertices[indiceDebug + 5] = vertices[indice + 2] + vertices[indice + 7];
    }

    unsigned int debugVBO;
    glGenBuffers(1, &debugVBO);
    glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(debugVertices), debugVertices, GL_STATIC_DRAW);

    unsigned int debugVAO;
    glGenVertexArrays(1, &debugVAO);
    glBindVertexArray(debugVAO);
    glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void debugNormals()
{
    glDrawArrays(GL_LINE, 0, 72);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MyLittleMoteur", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader objectShader("../shader/shader.vs", "../shader/shader.fs");
    Shader lightShader("../shader/lightShader.vs", "../shader/lightShader.fs");

    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../texture/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("../texture/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto lightOrigin = glm::vec3(0.0f, 0.0f, 1.0f);
    auto lightPosition = lightOrigin;
    auto lightColor = glm::vec3();

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = (float) glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        processInput(window, camera);

        lightPosition = lightOrigin + glm::vec3(5 * sin(glfwGetTime()),0.0,0.0);
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        //Draw light
        auto lightModel = glm::translate(glm::mat4(1.0), lightPosition);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        lightShader.use();
        lightShader.setMat4("transform", glm::mat4(1.0f));
        lightShader.setMat4("model", lightModel);
        lightShader.setMat4("view", camera.GetLookAt());
        lightShader.setMat4("projection", camera.GetProjection());
        lightShader.setVec3("lightColor", lightColor);


        glDrawArrays(GL_TRIANGLES, 0, 36);


        //draw objects
        objectShader.use(); 
        objectShader.setInt("texture1", 0); 
        objectShader.setInt("texture2", 1);
        objectShader.setFloat("time", (float) glfwGetTime());
        objectShader.setMat4("transform", trans);
        objectShader.setMat4("view", camera.GetLookAt());
        objectShader.setMat4("projection", camera.GetProjection());
        objectShader.setVec3("viewPosition", camera.Position.x, camera.Position.y, camera.Position.z);
        //material
        objectShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        objectShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        objectShader.setVec3("material.specular", 1.0f, 0.5f, 0.31f);
        objectShader.setFloat("material.shininess", 32.0f);
        //light
        glm::vec3 diffuseColor = 0.5f * lightColor;
        glm::vec3 ambientColor = 0.2f * diffuseColor;

        objectShader.setVec3("light.ambient", ambientColor);
        objectShader.setVec3("light.diffuse", diffuseColor);
        objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        objectShader.setVec3("light.position", lightPosition);

        glBindVertexArray(VAO);
        for (glm::vec3 position : cubePositions)
        {
            auto translate = glm::translate(glm::mat4(1.0f), position);
            objectShader.setMat4("model", translate);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}