#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in vec2 vertex_tex_coord;

out vec3 vert_position;
out vec3 model_normal;
out vec2 texCoord;

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;
uniform bool tile_textures;

void main()
{
	if(tile_textures)
	{
		texCoord = vertex_tex_coord * 10;
	}
	else
	{
		texCoord = vertex_tex_coord;
	}
	model_normal = vertex_normal;
	vert_position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}