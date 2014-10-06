#include "GoochShader.h"

GoochShader::GoochShader(void)
{
	this->inval();
}

GoochShader::~GoochShader(void)
{
}

void GoochShader::subInval(void)
{
	//Invalidate any special data here
	this->warm_color_handle = BAD_GL_VALUE;
	this->cool_color_handle = BAD_GL_VALUE;
	this->diffuse_warm_handle = BAD_GL_VALUE;
	this->diffuse_cool_handle = BAD_GL_VALUE;
	Shader::inval();
}

void GoochShader::subTakeDown(void)
{
	//Do any special cleanup here
	Shader::TakeDown();
}

//ARG1 = warmColor (vec3 *)
//ARG2 = coolColor (vec3 *)
//ARG3 = diffuseWarm (float *)
//ARG4 = diffuseCool (float *)
void GoochShader::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	glUniform3fv(this->warm_color_handle, 1, (GLfloat *) arg1);
	glUniform3fv(this->cool_color_handle, 1, (GLfloat *) arg2);
	glUniform1f(this->diffuse_warm_handle, *((GLfloat *) arg3));
	glUniform1f(this->diffuse_cool_handle, *((GLfloat *) arg4));
}

void GoochShader::subInit(void)
{
	this->warm_color_handle = glGetUniformLocation(this->program_id, "warmColor");
	this->cool_color_handle = glGetUniformLocation(this->program_id, "coolColor");
	this->diffuse_warm_handle = glGetUniformLocation(this->program_id, "diffuseWarm");
	this->diffuse_cool_handle = glGetUniformLocation(this->program_id, "diffuseCool");
	this->position_handle = glGetUniformLocation(this->program_id, "light_position"); //Different name in gooch
}
