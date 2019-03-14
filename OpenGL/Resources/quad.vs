#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

uniform float currentTime;

void main() {
	float s = (sin(currentTime/5)/cos(currentTime/5))/2;
	float c = (cos(currentTime/5)/sin(currentTime/5))/2;
	mat2 rot = mat2(c, s, -s, c);
	vec2 pos = rot * position.xy;
	gl_Position = vec4(pos, position.z, 1);
	fragColor = color;
	fragTexCoord = texCoord;
} 
