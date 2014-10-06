#version 400

layout (location = 0) out vec4 fragColor;

in float NdotL;
in vec3 reflectVec;
in vec3 viewVec;
in vec2 texCoord;

//Material info
uniform float shininess;

//Information on the Gooch shading

uniform	vec3 warmColor; //Dominant color for warm areas
uniform	vec3 coolColor; //Dominant color for cool areas
uniform	vec3 diffuseWarm; //Factor by which to show warm color rather than texture
uniform vec3 diffuseCool; //Factor by which to show cool color rather than texture

uniform sampler2D Tex1;

out vec4 FragColor;

void main()
{
	vec3 surfaceColor = vec3(texture(Tex1, texCoord));
	vec3 kcool = min(coolColor + diffuseCool * surfaceColor, 1.0);
	vec3 kwarm = min(warmColor + diffuseWarm * surfaceColor, 1.0);
	vec3 kfinal = mix(kcool, kwarm, NdotL); // Final color is an interpolated value between the cool color and warm color 
											// based on the angle between the surface and light
											
	//The remst is the standard Phong specular calcuation

	vec3 reflect_norm = normalize(reflectVec);
	vec3 view_norm = normalize(viewVec);

	float spec = max(dot(reflect_norm, view_norm), 0.0);
	spec = pow(spec, shininess);

	FragColor = vec4(min(kfinal + spec, 1.0), 1.0);
}