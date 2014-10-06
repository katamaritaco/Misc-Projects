#version 400
#extension GL_ARB_separate_shader_objects : enable
//Used for the skybox.

layout (location = 0) out vec4 fragColor;

in vec3 vert_position;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D Tex1;

// We opt for a set material, because we're only texturing the ground.
void main()
{
	vec4 texColor = texture(Tex1, texCoord);
	fragColor = texColor;
}