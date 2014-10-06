#include "SubShader.h"


SubShader::SubShader(void)
{
	this->inval();
}

SubShader::~SubShader(void)
{
}

void SubShader::subInval(void)
{
	//Invalidate any special data here
	Shader::inval();
}

void SubShader::subTakeDown(void)
{
	//Do any special cleanup here
	Shader::TakeDown();
}

//ARG1 =
//ARG2 =
//ARG3 =
//ARG4 =
void SubShader::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
}

void SubShader::subInit(void)
{
	//Do any special initialization code here
}
