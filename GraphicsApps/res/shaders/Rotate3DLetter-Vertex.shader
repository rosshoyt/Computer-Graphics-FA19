#version 130								          
in vec2 point;								          
in vec3 color;								          
out vec4 vColor;							          
uniform mat4 view;                                    
void main() {
	gl_Position = view * vec4(point, 0, 1);		      
	vColor = vec4(color, 1);			              
}