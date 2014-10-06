#version 400
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec4 fragColor;

in vec3 lightResult;

void main()
{
	fragColor = vec4(lightResult, 1.0);
}