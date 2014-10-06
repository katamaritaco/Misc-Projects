//Code taken from the OpenGL shader cookbook.

#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;

out vec3 position;
out vec3 Color;

void main()
{
	Color = vertex_color;
	position = vertex_position;
	gl_Position =  mvp_matrix * vec4(position, 1.0);
}