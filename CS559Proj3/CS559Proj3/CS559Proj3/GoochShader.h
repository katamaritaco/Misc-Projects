//A subclass of Shader designed for use with Gooch shading

#pragma once
#include "shader.h"
class GoochShader :
	public Shader
{
public:
	GoochShader(void);
	~GoochShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);
	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void GoochShader::subInval(void);

	//Handles for Gooch uniforms
	GLuint warm_color_handle;
	GLuint cool_color_handle;
	GLuint diffuse_warm_handle;
	GLuint diffuse_cool_handle;
};

