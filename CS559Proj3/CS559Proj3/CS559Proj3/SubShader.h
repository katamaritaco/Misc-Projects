//A subclass for a special kind of shader.
//The intention here is that we not provide any extra public functions;
//Instead, use the sub{X} functions to provide special functionality.

#pragma once
#include "shader.h"
typedef Shader super;
class SubShader :
	public Shader
{
public:
	SubShader(void);
	~SubShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4); //Allow us to pass in four parameters for special setup
	void subInit(void); //Do any needed special initialization
	void subTakeDown(void); //Do any needed special take down
protected:
	void subInval(void); //Do any needed special invalidation
};

