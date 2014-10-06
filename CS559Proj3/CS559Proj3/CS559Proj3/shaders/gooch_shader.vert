#version 400

//Much of the below code is taken from The OpenGL Shading Language, 3rd Edition, by Randi J. Rost and Bill Licea-Kane.

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 3) in vec2 vertex_tex_coord;

out vec3 reflectVec;
out vec3 viewVec;
out float NdotL;
out vec2 texCoord;

uniform	vec4 light_position;
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
	vec3 normal = normalize(n_matrix * vertex_normal);
	vec3 vert_position = vec3(mv_matrix * vec4(vertex_position, 1.0));
	vec3 lightVec = normalize(vec3(light_position) - vert_position);
	reflectVec = normalize(reflect(-lightVec, normal));
	viewVec = normalize(-vert_position);
	NdotL = dot(lightVec, normal) * 0.5 + 0.5; //Normalize to [0, 1]

	//The above lines are calculating the vector between the vertex position and the light source,
	//so that we can apply warmer colors to the 'hot spot' and cooler colors elsewhere

	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}