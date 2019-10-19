// CubePersp.cpp
#include <glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>
#include <time.h>
#include <VecMat.h>
#include "GLXtras.h" 
#include "Vertex.h"

// GPU identifiers
GLuint vBuffer = 0;  
GLuint program = 0;   

// user input handling
float rotSpeed = .3f;               // deg rotation per #pixels dragged by mouse
vec2 mouseDown(0, 0);               // location of last mouse down
vec2 rotOld(0, 0), rotNew(0, 0);    // .x is rotation about Y-axis, in deg; .y about X-axis

void MouseButton(GLFWwindow* w, int butn, int action, int mods) {
    // called when mouse button pressed or released
    if (action == GLFW_PRESS) {
        // save reference for MouseDrag
        double x, y;
        glfwGetCursorPos(w, &x, &y);
        mouseDown = vec2((float)x, (float)y);
    }
    if (action == GLFW_RELEASE)
        // save reference rotation
        rotOld = rotNew;
}
void MouseMove(GLFWwindow* w, double x, double y) {
    if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // compute mouse drag difference, update rotation
        vec2 dif((float)x - mouseDown.x, (float)y - mouseDown.y);
        rotNew = rotOld + rotSpeed * dif;
    }
}
void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Cube
float l = -1, r = 1, b = -1, t = 1, n = -1, f = 1; // left, right, bottom, top, near, far
float points[][3] = { {l,b,n},{l,b,f},{l,t,n},{l,t,f},{r,b,n},{r,b,f},{r,t,n},{r,t,f} }; // 8 point
float colors[][3] = { {0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{0,0,0},{1,1,1} }; // 8 colors
int faces[][4] = { {1,3,2,0}, {6,7,5,4}, {4,5,1,0}, {3,7,6,2}, {2,6,4,0}, {5,7,3,1} }; // 6 faces
float fieldOfView = 30, cubeSize = .05f, cubeStretch = cubeSize;

void Display() {
    mat4 view = RotateY(rotNew.y) * RotateX(rotNew.x);
    SetUniform(program, "view", view);
    // clear to gray, use app's shader
    glClearColor(.5, .5, .5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    // set vertex feed for points and colors, then draw
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    VertexAttribPointer(program, "point", 2, sizeof(Vertex), (void*) 0);
    VertexAttribPointer(program, "color", 3, sizeof(Vertex), (void*) sizeof(vec2));
    glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, triangles);
    glFlush();
}

void InitVertexBuffer() {
    // make GPU buffer for points & colors, set it active buffer
    glGenBuffers(1, &vBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

bool InitShader() { 
    program = LinkProgramViaFile("res/shaders/Rotate3DLetter_Vertex.shader",
                                 "res/shaders/Rotate3DLetter_Pixel.shader");
    if (!program)
        printf("can't init shader program\n");
    return program != 0;
}

void ErrorGFLW(int id, const char *reason) {
    printf("GFLW error %i: %s\n", id, reason);
}

void Close() {
    // unbind vertex buffer and free GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vBuffer);
}

int main() {
    glfwSetErrorCallback(ErrorGFLW);
    if (!glfwInit())
        return 1;
    GLFWwindow *window = glfwCreateWindow(600, 600, "Colorful Letter", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwSetMouseButtonCallback(window, MouseButton);
    glfwSetCursorPosCallback(window, MouseMove);
    glfwSetKeyCallback(window, Keyboard);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    printf("GL version: %s\n", glGetString(GL_VERSION));
    PrintGLErrors();
    if (!InitShader())
        return 0;
    InitVertexBuffer();
    while (!glfwWindowShouldClose(window)) {
        Display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    Close();
    glfwDestroyWindow(window);
    glfwTerminate();
}
