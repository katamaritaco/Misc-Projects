#version 400
//NOTE: Adapted from the GLSL cookbook.

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

out vec3 normal;
out vec3 vert_position;
out vec3 vert_color;

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;

void main()
{
	normal = normalize(n_matrix * vertex_normal);
	vert_position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
	vert_color = vertex_color;
}