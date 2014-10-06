#pragma once
#include "shader.h"

//A standard Phong/texture shader that also uses dynamic shadows.

class ShaderWithShadows :
	public Shader
{
public:
	ShaderWithShadows(void);
	~ShaderWithShadows(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);

	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void subInval(void);
	GLuint shad_mat_handle;
	GLuint shad_buf_handle;
	GLuint shad_pass_handle;
	GLuint draw_shad_handle;
};

