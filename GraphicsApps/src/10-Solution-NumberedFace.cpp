// Ross Hoyt and Chris Downing - Assignment 5 (Exercise 10.2) - Phong face

#include <glad.h>
#include <glfw/glfw3.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include "GLXtras.h"
#include "Camera.h"
#include "Draw.h"
#include <Misc.h>
#include <Numbers.h>
#include "VecMat.h"
#include <algorithm>

// vertices for left half of face
vec3 leftPoints[] = {
	
	vec3(720,244,434), vec3(912,269,488),  vec3(1052,318,670),											// 0-2
	vec3(713,447,284), vec3(978,450,366),  vec3(1093,496,490),  vec3(1143,586,561), vec3(1173,732,687), // 3-7
	vec3(719,660,216), vec3(1018,593,308), vec3(1147,787,516),											// 8-10
	vec3(734,1103,50), vec3(793,951,196),  vec3(833,900,307),   vec3(1065,923,409),						// 11-14
	vec3(738,1275,176),vec3(898,1134,286), vec3(1100,1095,417), vec3(1128,1219,543),					// 15-18
	vec3(904,1298,241),vec3(1024,1356,333),																// 19-20
	vec3(720,1480,162),vec3(853,1578,201), vec3(957,1594,440),  vec3(1120,1255,818),					// 21-24
	vec3(710,1741,154),vec3(780,1802,554), vec3(977,1650,782),											// 25-27
	vec3(1185,914,653)

	// Original Points in provided file:
	//vec3(761, -268, 1225),	vec3(392, -429, 1167),	vec3(486, -629, 1281),	vec3(292, -726, 1084),
	//vec3(761, -669, 1344),	vec3(761, -735, 1359),	vec3(630, -710, 1331),	vec3(397, -727, 1233),
	//vec3(324, -812, 1142),	vec3(303, -846, 1060),	vec3(305, -934, 1070),	vec3(347, -918, 1124),
	//vec3(503, -823, 1254),	vec3(761, -885, 1312),	vec3(761, -951, 1335),	vec3(601, -1058, 1250),
	//vec3(394, -1044, 1210),	vec3(761, -1197, 1433),	vec3(242, -1002, 918),	vec3(315, -1179, 1100),
	//vec3(761, -1364, 1316),	vec3(400, -1190, 1185),	vec3(534, -1296, 1255),	vec3(761, -1434, 1318),
	//vec3(602, -1421, 1256),	vec3(360, -1356, 1137),	vec3(329, -1374, 1023),	vec3(335, -1447, 826),
	//vec3(360, -1479, 1042),	vec3(453, -1513, 1157),	vec3(761, -1552, 1287),	vec3(761, -1587, 1267),
	//vec3(761, -1804, 1279),	vec3(529, -1458, 1206),	vec3(622, -1563, 1235),	vec3(516, -1693, 1131),
	//vec3(410, -1594, 994),	vec3(494, -1710, 710),	vec3(492, -1816, 643),	vec3(761, -1979, 725),
	//vec3(761, -1819, 878),	vec3(545, -271, 1218),	vec3(402, -925, 1190),	vec3(506, -865, 1223),
	//vec3(554, -852, 1223),	vec3(583, -925, 1223),	vec3(641, -900, 1223),	vec3(450, -972, 1223),
	//vec3(535, -981, 1223),	vec3(599, -969, 1223),	vec3(629, -937, 1223),	vec3(670, -1001, 1263),
	//vec3(651, -1477, 1246),	vec3(761, -1488, 1276),	vec3(692, -1069, 1284),	vec3(761, -1070, 1376),
	//vec3(580, -1133, 1280),	vec3(606, -1206, 1273),	vec3(761, -1271, 1446),	vec3(761, -1329, 1316)
};

// triangles for left half of face
int leftTriangles[][3] = {
	{0,1,3}, {1,4,3}, {1,2,4}, {2,5,4}, {2,6,5}, 
	{3,4,8}, {4,9,8}, {4,5,10}, {4,9,10}, {5,6,10}, {6,7,10}, {7,28,10}, {7,24,28},
	{8,9,13},{8,13,12}, {8,12,11}, {9,10,14}, {9,14,13}, {10,28,18}, {10,18,17}, {10,17,14},
	{11,12,16}, {11,16,15}, {12,13,16}, {13,14,16}, {14,17,16}, 
	{15,16,19}, {15,19,21}, {16,17,18}, {16,18,20}, {16,20,19}, {17,10,18}, {18,28,24}, {18,24,23}, {18,23,20}, 
	{19,20,21}, {20,23,22}, {20,22,21}, 
	{21,22,25}, {22,23,25}, {23,24,27}, {23,27,26}, {23,26,25}, 
	
	// Original Triangles in provided file:
	//{0, 1, 2},		{1, 3, 2},		{0, 2, 4},	 	{3, 7, 2},		{7, 12, 6},		{2, 7, 6},
	//{2, 6, 4},		{4, 6, 5},		{5, 6, 13},		{6, 12, 13},  	{3, 8, 7},		{7, 8, 12},
	//{3, 18, 9},		{9, 18, 10},	{3, 9, 8},		{9, 10, 8},		{10, 11, 8},	{8, 11, 12},
	//{18, 16, 10},	{10, 16, 11},	{18, 19, 16},	{19, 21, 16},	{21, 22, 16},	{19, 26, 25},
	//{19, 25, 21},	{25, 22, 21},	{26, 27, 28},	{26, 28, 25},	{28, 29, 25},	{25, 29, 22},
	//{22, 29, 33},	{33, 24, 22},	{24, 23, 22},	{22, 23, 20},	{28, 36, 29},	{36, 35, 29},
	//{29, 35, 34},	{29, 34, 33},	{33, 34, 30},	{34, 31, 30},	{36, 37, 35},	{37, 38, 39},
	//{35, 32, 34},	{34, 32, 31},	{37, 40, 35},	{37, 39, 40},	{35, 40, 32},	{41, 1, 0},
	//{11, 42, 12},	{11, 16, 42},	{42, 16, 47},	{42, 47, 43},	{42, 43, 12},	{43, 44, 12},
	//{47, 48, 43},	{43, 48, 45},	{48, 49, 45},	{49, 50, 45},	{45, 50, 46},	{44, 45, 46},
	//{46, 50, 14},	{49, 51, 50},	{50, 51, 14},	{47, 16, 48},	{16, 15, 48},	{48, 15, 49},
	//{49, 15, 51},	{33, 52, 24},	{33, 30, 52},	{52, 30, 53},	{52, 53, 23},	{24, 52, 23},
	//{16, 56, 15},	{15, 56, 54},	{15, 54, 51},	{51, 54, 14},	{54, 55, 14},	{54, 17, 55},
	//{16, 22, 56},	{22, 57, 56},	{56, 57, 54},	{22, 59, 57},	{57, 59, 58},	{57, 17, 54},
	//{57, 58, 17},	{22, 20, 59},	{12, 44, 13},	{44, 46, 13},	{46, 14, 13},	{44, 43, 45},
	//{18, 26, 19},	{18, 27, 26},	{27, 36, 28},	{27, 37, 36}
};

// entire face
const int nLeftPoints = sizeof(leftPoints)/sizeof(leftPoints[0]);
const int nLeftTriangles = sizeof(leftTriangles)/sizeof(leftTriangles[0]);
const int npoints = 2*nLeftPoints, ntriangles = 2*nLeftTriangles;
vec3 normals[npoints], points[npoints];
int triangles[ntriangles][3];
int sizePts = sizeof(points);
int midX = leftPoints[0].x; // midpoint of face

// shaders
const char *vShader = "\
	#version 130												\n\
	in vec3 point;												\n\
	in vec3 normal;												\n\
	uniform mat4 modelview;										\n\
	uniform mat4 persp;											\n\
	out vec3 vPoint;											\n\
	out vec3 vNormal;											\n\
	void main() {												\n\
		vPoint = (modelview*vec4(point, 1)).xyz;				\n\
		vNormal = (modelview*vec4(normal, 0)).xyz;				\n\
		gl_Position = persp*vec4(vPoint, 1);					\n\
	}";

const char *pShader = "\
	#version 130												\n\
	in vec3 vPoint;												\n\
	in vec3 vNormal;											\n\
	uniform float a = 0.1;										\n\
	uniform vec3 lightPos = vec3(-1, 0, -2);					\n\
	uniform vec3 color = vec3(1, 1, 1);							\n\
	out vec4 pColor;											\n\
	void main() {												\n\
		vec3 N = normalize(vNormal);							\n\
		vec3 L = normalize(lightPos-vPoint);					\n\
		vec3 R = reflect(L, N);									\n\
		vec3 E = normalize(vPoint);								\n\
		float d = abs(dot(L, N));								\n\
		float h = max(0, dot(R, E));							\n\
		float s = pow(h, 100);									\n\
		float intensity = clamp(a+d+s, 0, 1);					\n\
		pColor = vec4(intensity*color, 1);						\n\
	}";

// OpenGL identifiers
GLuint vBuffer = 0, program = 0;

// window size and camera
int winWidth = 800, winHeight = 1000;
Camera camera(winWidth, winHeight, vec3(0, 0, 0), vec3(0, 0, -5), 30, 0.001f, 500, false);

// display
bool annotate = false;

void Display(GLFWwindow* w) {
	// clear to gray, use app's shader
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// use program, bind vertex buffer, set vertex feed, set uniforms
	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	VertexAttribPointer(program, "point", 3, 0, (void *) 0);
	VertexAttribPointer(program, "normal", 3, 0, (void *) sizePts);
	SetUniform(program, "modelview", camera.modelview);
	SetUniform(program, "persp", camera.persp);
	// set color, draw shape
	SetUniform(program, "color", vec3(1, 1, 1));
	glDrawElements(GL_TRIANGLES, 3*ntriangles, GL_UNSIGNED_INT, triangles);
	// optional vertex and triangle annotation
	if (annotate) {
		glDisable(GL_DEPTH_TEST);
		SetUniform(program, "color", vec3(0, 0, 1));
		for (int i = 0; i < ntriangles; i++)
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, &triangles[i]);
		for (int i = 0; i < npoints; i++)
			Number(points[i], camera.fullview, i, vec3(0,0,0), 10);
	}
	glFlush();
}

// scale points to lie within +/-1
void Normalize() {
	vec3 mn(FLT_MAX), mx(-FLT_MAX);
	for (int i = 0; i < npoints; i++) {
		vec3 p = points[i];
		for (int k = 0; k < 3; k++) {
			if (p[k] < mn[k]) mn[k] = p[k];
			if (p[k] > mx[k]) mx[k] = p[k];
		}
	}
	vec3 center = .5f*(mn+mx), range = mx-mn;
	float maxrange = std::max(range.x, std::max(range.y, range.z)), s = 2/maxrange;
	for (int i = 0; i < npoints; i++)
		points[i] = s*(points[i]-center);
}

bool Mid(float x) { return fabs(x-midX) < .0001f; }
	// is x close to the middle of the face?

void Reflect() {
	// copy left face vertices and triangles to full face
	for (int i = 0; i < nLeftPoints; ++i)
		points[i] = leftPoints[i];
	for (int i = 0; i < nLeftTriangles; ++i) {
		int *tLeft = leftTriangles[i], *t = triangles[i];
		for (int k = 0; k < 3; k++)
			t[k] = tLeft[k];
	}
	// fill second half of points, reflecting points around midX
	for (int i = 0; i < nLeftPoints; ++i)
		points[i+nLeftPoints] = vec3(2*midX-leftPoints[i].x, leftPoints[i].y, leftPoints[i].z);
	// fill second half of triangles
	for (int i = 0; i < nLeftTriangles; ++i) {
		int *t = leftTriangles[i];
		// test each triangle vertex for proximity to midX; if close, use original vertex, else use reflected vertex
		for (int k = 0; k < 3; k++)
			triangles[i+nLeftTriangles][2-k] = Mid(points[t[k]].x)? t[k] : t[k]+nLeftPoints;
			// 2-k reverses order of reflected triangles to ensure still ccw
	}
}

void ComputeNormals() {
	// initialize to zero
	for (int i = 0; i < npoints; ++i)
		normals[i] = vec3(0, 0, 0);
	// for each triangle: compute surface normal and add to each corresponding vertex normal
	for (int i = 0; i < ntriangles; ++i) {
		int* t = triangles[i];
		vec3 p1(points[t[0]]), p2(points[t[1]]), p3(points[t[2]]);
		vec3 n = normalize(cross(p3-p2, p2-p1));
		for (int k = 0; k < 3; k++)
			normals[t[k]] += n;
	}
	// set normals to unit length
	for (int i = 0; i < npoints; ++i)
		normals[i] = normalize(normals[i]);
}

void Resize(GLFWwindow* w, int width, int height) {
	camera.Resize(width, height);
	glViewport(0, 0, width, height);
}

bool Shift(GLFWwindow *w) {
	return glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
		   glfwGetKey(w, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
}

void MouseButton(GLFWwindow* w, int butn, int action, int mods) {
	if (action == GLFW_PRESS) {
		double x, y;
		glfwGetCursorPos(w, &x, &y);
		camera.MouseDown((int) x, (int) y);
	}
	if (action == GLFW_RELEASE)
		camera.MouseUp();
}

void MouseWheel(GLFWwindow *w, double xoffset, double yoffset) {
	camera.MouseWheel((int) yoffset, Shift(w));
}

void MouseMove(GLFWwindow* w, double x, double y) {
	if (glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera.MouseDrag((int) x, (int) y, Shift(w));
}

void Key(GLFWwindow* w, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		switch (key) {
			case 'A':
				annotate = !annotate;
				break;
		}
}

void InitVertexBuffer() {
	// create GPU buffer, make it active
	glGenBuffers(1, &vBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	// allocate memory for points and normals
	glBufferData(GL_ARRAY_BUFFER, 2*sizePts, NULL, GL_STATIC_DRAW);
	// copy
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizePts, &points[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizePts, sizePts, &normals[0]);
}

int main() {
	if (!glfwInit())
		return 1;
	GLFWwindow *w = glfwCreateWindow(winWidth, winHeight, "Face", NULL, NULL);
	if (!w) {
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	PrintGLErrors();
	program = LinkProgramViaCode(&vShader, &pShader);
	Reflect();				// reflect leftPoints to create entire face
	Normalize();			// set points within +/- 1.
	ComputeNormals();		// estimate vertex normals from surrounding triangles
	InitVertexBuffer();		// store in GPU
	glfwSetKeyCallback(w, Key);
	glfwSetScrollCallback(w, MouseWheel);
	glfwSetMouseButtonCallback(w, MouseButton);
	glfwSetCursorPosCallback(w, MouseMove);
	glfwSetWindowSizeCallback(w, Resize);
    printf("Usage:\n\tA: toggle annotation\n");
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(w)) {
		Display(w);
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vBuffer);
	glfwDestroyWindow(w);
	glfwTerminate();
}
