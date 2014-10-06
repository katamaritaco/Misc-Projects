#version 400

layout (location = 0) out vec4 fragColor;

in vec3 Color;

void main()
{
	fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}