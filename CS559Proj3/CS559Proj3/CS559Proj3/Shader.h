#pragma once
#include "glutInclude.h"
#include <assert.h>
#include <sstream>
#include "MaterialInfo.h"
#include "Textures.h"

#define BAD_GL_VALUE GLuint(-1)

//Class for a basic shader that supports Phong and texturing.

//This enum is used to define what kind of shader we're using.
//In this implementation, only NONE, NORM, TEX_W_SHADOWS, TEX_NO_LIGHTING, GOOCH, FIRE_NOISE, and NOISE_NORMAL are used
enum SHADER_TYPE {NONE, FLAT, GOURAUD, PHONG, DEBUG_POS, GOOCH, MAX,\
	NORM, DEBUG_NORM, TEX, TEX_W_SHADOWS, TEX_NO_LIGHTING, FIRE_NOISE, NOISE_NORMAL}; 
class Shader
{
public:
	Shader(void);
	~Shader(void);
	bool init(SHADER_TYPE t);
	virtual void subInit(void); //To be overridden
	void setup(const float time, const GLint * size, const GLfloat * proj, const GLfloat * mv, const GLfloat * mvp, const GLfloat * norm); //Sets up basics
	virtual void subSetup(void * arg1, void * arg2, void * arg3, void * arg4) { return; } //To be overridden
	void use(void);
	void lightSetup(lightInfo & l); //Sets up light location
	void materialSetup(materialInfo & m); //Sets up material properties
	void texSetup(TEXTURE_TYPE type, bool doTiles); //Sets up texture
	void TakeDown(void); 
	virtual void subTakeDown(void); //To be overridden
	void reload(SHADER_TYPE t); //Switches shader types; unused

	std::stringstream GetShaderLog(GLuint shader_id);
	std::stringstream Shader::GetProgramLog(GLuint program_id);

	SHADER_TYPE type;

	static GLint light_index; //OBSOLETE: was used with binding uniform block to pass down a LightInfo struct
	static GLuint light_handle; //OBSOLETE: was used with binding uniform block to pass down a LightInfo struct

protected:
	void inval(void);
	virtual void subInval(void);
	bool load(char * file, GLuint handle);
	static int bind_point; // [OBSOLETE] Binding locations for our uniform buffers.

	GLint time_handle;
	GLint size_handle; 

	// Matrix handles.
	GLint mv_mat_handle;
	GLint p_mat_handle;
	GLint mvp_mat_handle;
	GLint n_mat_handle; 

	GLint material_index; // Material uniform index location.
	GLuint material_handle; // Material buffer handle.

	GLint tex_handle; // Texture handle.
	GLint tile_handle; // Indicate if we tile our textures
	
	GLuint program_id; // Program handle.
	GLuint vertex_s_id; // Vertex shader handle.
	GLuint frag_s_id; // Fragment shader handle.

	GLint position_handle; // Light position
	GLint color_handle; // Light color modifier
	GLint amb_handle; // Light ambient component
	GLint diff_handle; // Light diffuse component
	GLint spec_handle; // Light specular component
	
	GLint ka_handle; // Material ambient component
	GLint kd_handle; // Material diffuse component
	GLint ks_handle; // Material specular component
	GLint shininess_handle; // Material specular exponent

	GLubyte * lightBuffer; // [OBSOLOETE] space for lighting info.
	GLubyte * matBuffer; // [OBSOLETE] space for material info.

};

