#version 400
#extension GL_ARB_separate_shader_objects : enable
//NOTE: Adapted from the GLSL cookbook.
//DESIGN NOTICE: For testing, we assume a standard Ka, Kd, Ks.
//Later, we can adjust these via stuffing in the material struct.
//TODO: Account for color.  How do we do that, anyways? Just multiply across? X

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

out vec3 lightResult;

uniform lightInfo {
	vec4 position;
	vec3 color;
	vec3 amb;
	vec3 diff;
	vec3 spec;
	int spec_exp; //TODO: Have this here or in other location?
};

uniform materialInfo {
	vec3 kA;
	vec3 kD;
	vec3 kS;
	float shininess;
};

//TODO: Can we stuff down multiple lightInfos?

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;

void main()
{
	vec3 tNorm = normalize (n_matrix * vertex_normal);

	vec4 eyeCoor = mv_matrix * vec4(vertex_position, 1.0);
	vec3 s = normalize(vec3(position - eyeCoor));
	vec3 v = normalize(vec3(-eyeCoor.xyz)); //TODO: What's with the swizzling?
	vec3 r = reflect(-s, tNorm);
	vec3 amb_comp = amb * kA;
	float sDotNorm = max(dot(s, tNorm), 0.0);
	vec3 diff_comp = diff * kD * sDotNorm;
	vec3 spec_comp = vec3(0.0);
	if (sDotNorm > 0.0 )
	{
		spec_comp = spec * kS * pow(max(dot(r, v), 0.0), shininess);
	}
	lightResult = vertex_color * (amb_comp + diff_comp) + spec_comp;
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}