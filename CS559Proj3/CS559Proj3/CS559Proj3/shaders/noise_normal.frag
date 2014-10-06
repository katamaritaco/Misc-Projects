#version 400
#extension GL_ARB_separate_shader_objects : enable
//Used for the skybox.

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec2 texCoord;

//Information on the light
uniform	vec4 position;
uniform	vec3 amb;
uniform	vec3 diff;
uniform	vec3 spec;

//Information on the material
uniform	vec3 kA;
uniform	vec3 kD;
uniform	vec3 kS;
uniform	float shininess;

uniform float time;
uniform sampler2D Tex1;
uniform sampler3D noiseTex;

vec3 phong (vec3 normal, vec3 diff_color)
{
	vec3 n = normalize(abs(normal)); 
	vec3 s = normalize(vec3(position) - vert_position);
	vec3 v = normalize(vec3(-vert_position));
	vec3 r = reflect(-s, n);
	vec3 amb_comp = amb * kA;
	float sDotNorm = max(dot(s, n), 0.0);
	vec3 diff_comp = diff * kD * sDotNorm;
	vec3 spec_comp = vec3(0.0);
	if (sDotNorm > 0.0 )
	{
		spec_comp = spec * kS * pow(max(dot(r, v), 0.0), shininess);
	}
	return ((diff_color * amb_comp + diff_comp) + spec_comp);
}

// This shader is essentially just playing around with noise.
// We access our noise texture at a point decided by the texture coordinate and 
// an arctan function on time, then combine that with another function on time to
// adjust the normal further.
void main()
{
	vec4 noiseNorm = texture(noiseTex, vec3(texCoord, atan(time/15000.0)));
	noiseNorm = vec4(noiseNorm.x, sin(time/150), noiseNorm.z, 1.0);
	vec4 texColor = texture(Tex1, texCoord);
	
	vec3 color = phong(noiseNorm.rgb, texColor.rgb);

	fragColor = vec4(color, 1.0);

}