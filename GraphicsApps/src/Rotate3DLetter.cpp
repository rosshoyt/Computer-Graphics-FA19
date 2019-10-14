// Rotating3DLetter.cpp
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
float rotSpeed = .3f;				// deg rotation per #pixels dragged by mouse
vec2 mouseDown(0, 0);				// location of last mouse down
vec2 rotOld(0, 0), rotNew(0, 0);	// .x is rotation about Y-axis, in deg; .y about X-axis
void MouseButton(GLFWwindow* w, int butn, int action, int mods) {
	// called when mouse button pressed or released
	if (action == GLFW_PRESS) {
		// save reference for MouseDrag
		double x, y;
		glfwGetCursorPos(w, &x, &y);
		mouseDown = vec2((float)x, (float)y);
	}
	if (action == GLFW_RELEASE)
		//save reference rotation
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

// H-Letter design
Vertex vertices[] = {
	Vertex(-.5f,-.8f,  0, 0, 1), Vertex(-.8f,-.8f,  1, 0, 0), // V0, V1
	Vertex(-.8f, .8f,  0, 0, 1), Vertex(-.5f, .8f,  0, 1, 0),
	Vertex(-.5f, .13f, 0, 0, 1), Vertex( .5f, .13f, 0, 1, 0),
	Vertex(-.5f,-.13f, 0, 0, 1), Vertex( .5f,-.13f, 1, 0, 0), // V6, V7
	Vertex( .8f,-.8f,  0, 0, 1), Vertex( .5f,-.8f,  1, 0, 0),
	Vertex( .5f, .8f,  0, 0, 1), Vertex( .8f, .8f,  0, 1, 0),
	Vertex(-.8f,-.13f, 1, 0, 0), Vertex(-.8f, .13f, 0, 0, 1), // V12, 13
	Vertex( .8f,-.13f, 1, 0, 0), Vertex( .8f, .13f, 0, 0, 1) 
};
int triangles[][3] = {
	{0,1, 12},{2, 3,4},{4, 5, 6},{5,6, 7},{8, 9,7},{10,11,15},
	{0,12, 6},{2,13,4},{6,12,13},{6,4,13},{8,14,7},{10,15, 5},
	{7,14,15},{7,5,15}
};

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
	//program = LinkProgramViaCode(&vertexShader, &pixelShader);
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