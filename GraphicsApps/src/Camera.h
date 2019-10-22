#ifndef CAMERA_H
#define CAMERA_H
#include <VecMat.h>


class Camera {
private:	
	int width, height;
	float fov;
	vec3 rotOld, rotNew;     // .x is rotation about Y-axis, in deg; .y about X-axis
	vec3 tranOld, tranNew;	 // old/new translate
	vec2 mouseDown;          // location of last mouse down
	float rotSpeed = .3f;    // deg rotation per #pixels dragged by mouse
	float tranSpeed = .01f;
public:
	Camera(int width, int height, vec3 rot, vec3 trans, float fov) :
		width(width), height(height), fov(fov),
		rotOld(0, 0, 0), rotNew(rot), tranOld(0, 0, 0), tranNew(trans),
		mouseDown(0,0)
		
	{}
	
	mat4 fullview() {
		mat4 rot = RotateY(rotNew.x) * RotateX(rotNew.y);
		mat4 tran = Translate(tranNew);
		return tran * rot;
	}
	void MouseDown(int x, int y) {
		mouseDown = vec2((float)x, (float)y);
	}
	void MouseUp() {
		// save reference rotation
		rotOld = rotNew;
		tranOld = tranNew;
	}
	void MouseMove(double x, double y) {
		vec2 mouse((float)x, (float)y);
		vec2 dif = mouse - mouseDown;
		rotNew = rotOld + rotSpeed * vec3(dif, 1);
	}
	void MouseWheel(double xoffset, double yoffset) {
		tranNew.z += (yoffset + xoffset) * .25; // scales mouse wheel values
	}

};
 



#endif // !CAMERA
