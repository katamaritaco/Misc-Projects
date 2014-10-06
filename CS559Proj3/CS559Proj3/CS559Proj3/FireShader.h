#pragma once
#include "shader.h"
//The name "FireShader" is a slight misnomer, as this class is also used in our other noise-related shader,
//which uses noise to adjust normals, rather than create a 'fire' effect.
class FireShader :
	public Shader
{
public:
	FireShader(void);
	~FireShader(void);
	void subSetup(void * arg1, void * arg2, void * arg3, void * arg4);

	void subInit(void); //To be overridden
	void subTakeDown(void);
protected:
	void subInval(void);
	GLuint noiseHandle;
	GLuint activeHandle;
};

