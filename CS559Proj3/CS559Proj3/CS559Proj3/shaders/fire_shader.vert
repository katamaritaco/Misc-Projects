#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in vec2 vertex_tex_coord;

out vec3 vert_position;
out vec3 normal;
out vec2 texCoord;

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;
uniform bool tile_textures;
uniform sampler3D noiseTex;
uniform float time;

void main()
{
	if(tile_textures)
	{
		texCoord = vertex_tex_coord * 10;
	}
	else
	{
		texCoord = vertex_tex_coord * 1;
	}
	normal = normalize(n_matrix * vertex_normal);
	vert_position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	vec3 shake_position = vertex_position + ((texture(noiseTex, vec3(vertex_position.xy, time/15000)) * 0.5).xyz); //Slightly modify vertex location based on time/noise
	gl_Position = mvp_matrix * vec4(shake_position, 1.0);
}