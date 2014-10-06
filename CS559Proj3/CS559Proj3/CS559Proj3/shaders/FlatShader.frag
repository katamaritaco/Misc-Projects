#version 400

layout (location = 0) out vec4 fragColor;

flat in vec3 lightResult;

void main()
{
	fragColor = vec4(lightResult, 1.0);
}