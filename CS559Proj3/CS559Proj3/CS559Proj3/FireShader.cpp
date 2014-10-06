#include "FireShader.h"


FireShader::FireShader(void)
{
	this->inval();
}

FireShader::~FireShader(void)
{
}

void FireShader::subInval(void)
{
	//Invalidate any special data here
	this->noiseHandle = BAD_GL_VALUE;
	this->activeHandle = BAD_GL_VALUE;
	Shader::inval();
}

void FireShader::subTakeDown(void)
{
	//Do any special cleanup here
	Shader::TakeDown();
}

//ARG1 = Is the ball active? (bool *)
//ARG2 = N/A
//ARG3 = N/A
//ARG4 = N/A
void FireShader::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	glUniform1i(this->noiseHandle, int(NOISE));
	glUniform1i(this->activeHandle, *((bool *)arg1));
}

void FireShader::subInit(void)
{
	//Do any special initialization code here
	this->noiseHandle = glGetUniformLocation(this->program_id, "noiseTex");
	this->activeHandle = glGetUniformLocation(this->program_id, "isActive");
}
