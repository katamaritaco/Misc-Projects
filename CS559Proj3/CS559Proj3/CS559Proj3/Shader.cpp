#include "Shader.h"
#include <iostream>

//Much of the code in this class is adapted from Perry Kivolowitz's hello world.
//However, I attempted to avoid cutting and pasting, instead typing by hand with my own variable names;
//the hope is that in doing so, I will think about what the code I'm adapting means.

Shader::Shader(void)
{
	inval(); 
}

Shader::~Shader(void)
{
}

void Shader::subInit(void)
{
	return;
}

void Shader::subTakeDown(void)
{
	TakeDown();
}
/*
void Shader::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	return;
}*/

void Shader::subInval(void)
{
	inval();
}

/*
void Shader::subSetup(void * arg1, void * arg2, void * arg3, void * arg4)
{
	return;
}*/

//Ensures that all of our internal values are in a 'bad' state so we can check them later.
void Shader::inval()
{
	this->frag_s_id = BAD_GL_VALUE;
	this->mv_mat_handle = BAD_GL_VALUE;
	this->n_mat_handle = BAD_GL_VALUE;
	this->program_id = BAD_GL_VALUE;
	this->p_mat_handle = BAD_GL_VALUE;
	this->time_handle = BAD_GL_VALUE;
	this->vertex_s_id = BAD_GL_VALUE;
	this->light_handle = BAD_GL_VALUE;
	this->light_index = BAD_GL_VALUE;
	this->material_handle = BAD_GL_VALUE;
	this->material_index = BAD_GL_VALUE;

	this->position_handle = BAD_GL_VALUE;
	this->color_handle = BAD_GL_VALUE;
	this->amb_handle = BAD_GL_VALUE;
	this->diff_handle = BAD_GL_VALUE;
	this->spec_handle = BAD_GL_VALUE;

	this->ka_handle = BAD_GL_VALUE;
	this->kd_handle = BAD_GL_VALUE;
	this->ks_handle = BAD_GL_VALUE;

	this->tex_handle = BAD_GL_VALUE;
	this->tile_handle = BAD_GL_VALUE;

	this->lightBuffer = NULL;
	this->matBuffer = NULL;

}

void Shader::reload(SHADER_TYPE t)
{
	GLReturnedError("Shader - reload on entry\n");
	this->subTakeDown();
	bool boot = this->init(t);
	assert(boot);
	this->subInit();
	GLReturnedError("Shader - reload on exit\n");
}

void Shader::use(void)
{
	GLReturnedError("Shader - use on entry\n");
	assert(this->program_id != BAD_GL_VALUE);
	glUseProgram(this->program_id);
	GLReturnedError("Shader - use on exit\n");
}

void Shader::TakeDown(void)
{
	
	GLint temp = 0;
	GLsizei size = 0;

	if (this->program_id != (GLuint) -1)
	{
		//TODO: This fails when being called as part of an object destructor.
		//The question is, why?
		//Answer: because the GL context might already be destroyed.

		//Taken from Perry Kivolowitz's code.
		glGetProgramiv(this->program_id, GL_ATTACHED_SHADERS, &temp); // fetch number of attached shaders
		if (temp > 0)
		{
			GLuint * shader_list = new GLuint[temp]; 
			glGetAttachedShaders(this->program_id, temp, &size, shader_list); //get handles to attached shaders
			for (GLsizei i = 0; i < size; i++)
			{
				glDetachShader(this->program_id, shader_list[i]);
				// The shaders were marked for deletion
				// immediately after they were created.
			}
			delete [] shader_list;
		}

		glDeleteProgram(this->program_id);
	}
	// We need to take care of our uniform object buffers if we've used them.
	if (this->lightBuffer != NULL) 
	{
			free(lightBuffer);
			glDeleteBuffers(1, &this->light_handle);
			this->light_handle = BAD_GL_VALUE;
			this->light_index = BAD_GL_VALUE;
			Shader::bind_point--;
	}
	if (this->matBuffer != NULL) 
	{
			free(matBuffer);
			glDeleteBuffers(1, &this->material_handle);
			this->material_handle = BAD_GL_VALUE;
			this->material_index = BAD_GL_VALUE;
			Shader::bind_point--;
	}
	inval();
	GLReturnedError("Shader TakeDown - on exit\n");
}

void Shader::setup(const float time, const GLint * size, const GLfloat * proj, const GLfloat * mv, const GLfloat * mvp, const GLfloat * norm)
{
	GLint temp = 0;
	
	GLReturnedError("Shader - setup on entry\n");
	glUniform1f(this->time_handle, time);
	glUniform2iv(this->size_handle, 1, size); //TODO: What is that 1 for? Counter apparently.  Which means...?
	glUniformMatrix4fv(this->mv_mat_handle, 1, GL_FALSE, mv);
	glUniformMatrix4fv(this->p_mat_handle, 1, GL_FALSE, proj);
	glUniformMatrix4fv(this->mvp_mat_handle, 1, GL_FALSE, mvp);
	glUniformMatrix3fv(this->n_mat_handle, 1, GL_FALSE, norm); 
	GLReturnedError("Shader - setup on exit\n");
}

void Shader::lightSetup(lightInfo & l)
{
	glUniform4fv(this->position_handle, 1, glm::value_ptr(l.position));
	glUniform3fv(this->color_handle, 1, glm::value_ptr(l.color));
	glUniform3fv(this->amb_handle, 1, glm::value_ptr(l.amb));
	glUniform3fv(this->diff_handle, 1, glm::value_ptr(l.diff));
	glUniform3fv(this->spec_handle, 1, glm::value_ptr(l.spec));
}
/*
void Shader::lightSetup(lightInfo & l)
{
	//Code adapted from the GLSL cookbook.
	//TODO: No need to change light if already present. X
	//TODO: Pass by reference? X
	GLReturnedError("Shader - lightSetup on entry\n");
	if (this->light_index != BAD_GL_VALUE && this->light_handle == BAD_GL_VALUE)
	{
		GLint bindingPoint = Shader::bind_point;
		GLint blockSize = 0;
		glGetActiveUniformBlockiv(this->program_id, this->light_index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize == 0) return; // Help avoid corner cases.
		if (this->lightBuffer != NULL) 
		{
				free(lightBuffer);
				glDeleteBuffers(1, &this->light_handle);
				//TODO: I can't imagine this rapid alloc/free pattern is efficient. X We should avoid this now.
		}
		this->lightBuffer = (GLubyte *) malloc(blockSize);
		const GLchar * names[] = {"position", "color", "amb", "diff", "spec", "spec_exp"};
		GLuint indices[6];
		glGetUniformIndices(this->program_id, 6, names, indices);
		GLint offset[6];
		glGetActiveUniformsiv(this->program_id, 6, indices, GL_UNIFORM_OFFSET, offset);
		memcpy(lightBuffer + offset[0], &l.position, sizeof(glm::vec4));
		memcpy(lightBuffer + offset[1], &l.color, sizeof(glm::vec3));
		memcpy(lightBuffer + offset[2], &l.amb, sizeof(glm::vec3));
		memcpy(lightBuffer + offset[3], &l.diff, sizeof(glm::vec3));
		memcpy(lightBuffer + offset[4], &l.spec, sizeof(glm::vec3));
		memcpy(lightBuffer + offset[5], &l.spec_exp, sizeof(GLint));
		
		glUniformBlockBinding(this->program_id, this->light_index, bindingPoint);
		glGenBuffers(1, &this->light_handle);
		glBindBuffer( GL_UNIFORM_BUFFER, light_handle);
		glBufferData( GL_UNIFORM_BUFFER, blockSize, this->lightBuffer, GL_DYNAMIC_DRAW);
		glBindBufferBase ( GL_UNIFORM_BUFFER, bindingPoint, this->light_handle);
		Shader::bind_point++;
	}
		GLReturnedError("Shader - lightSetup on exit\n");
}
*/

void Shader::materialSetup(materialInfo & m)
{
	glUniform3fv(this->ka_handle, 1, glm::value_ptr(m.kA));
	glUniform3fv(this->kd_handle, 1, glm::value_ptr(m.kD));
	glUniform3fv(this->ks_handle, 1, glm::value_ptr(m.kS));
	glUniform1f(this->shininess_handle, m.shininess);
}

/*
void Shader::materialSetup(materialInfo & m)
{	
	GLReturnedError("Shader - materialSetup on entry\n");
	if (this->material_index != BAD_GL_VALUE && this->material_handle == BAD_GL_VALUE)
	{
		GLint blockSize = 0;
		GLint bindingPoint = Shader::bind_point;
		glGetActiveUniformBlockiv(this->program_id, this->material_index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		if(blockSize == 0) return; // Helps protect against corner cases where init hasn't properly finished.  (I think.)
		if (this->matBuffer != NULL) 
		{
				free(matBuffer);
				glDeleteBuffers(1, &this->material_handle);
		}
		int test = sizeof(glm::vec3);
		test = sizeof(materialInfo);
		test = GL_MAX_VERTEX_UNIFORM_BLOCKS;
		this->matBuffer = (GLubyte *) malloc(blockSize);
		const GLchar * names[] = {"kA", "kD", "kS", "shininess"};
		GLuint indices[4];
		glGetUniformIndices(this->program_id, 4, names, indices);
		GLint offset[4];
		glGetActiveUniformsiv(this->program_id, 4, indices, GL_UNIFORM_OFFSET, offset);
		memcpy(matBuffer + offset[0], &m.kA, sizeof(glm::vec3));
		memcpy(matBuffer + offset[1], &m.kD, sizeof(glm::vec3));
		memcpy(matBuffer + offset[2], &m.kS, sizeof(glm::vec3));
		memcpy(matBuffer + offset[3], &m.shininess, sizeof(float));

		glUniformBlockBinding(this->program_id, this->material_index, bindingPoint);
		glGenBuffers(1, &this->material_handle);
		glBindBuffer( GL_UNIFORM_BUFFER, material_handle);
		glBufferData( GL_UNIFORM_BUFFER, blockSize, this->matBuffer, GL_STATIC_DRAW);
		glBindBufferBase ( GL_UNIFORM_BUFFER, bindingPoint, this->material_handle);
		Shader::bind_point++;
	}
		GLReturnedError("Shader - materialSetup on exit\n");
}*/

void Shader::texSetup(TEXTURE_TYPE type, bool doTiles)
{
	glUniform1i(this->tex_handle, int(type));
	glUniform1i(this->tile_handle, doTiles);
	return;
}

bool Shader::init(SHADER_TYPE t)
{
	if (GLReturnedError("Shader::Initialize - on entrance")) return false;
	this->type = t;
	char * vertex_shader_file;
	char * fragment_shader_file;
	switch (t)
	{
	case NONE:
		vertex_shader_file = "shaders\\no_shader.vert";
		fragment_shader_file = "shaders\\no_shader.frag";
		break;
	case PHONG:
		vertex_shader_file = "shaders\\Phong_shader.vert";
		fragment_shader_file = "shaders\\Phong_shader.frag";
		break;
	case GOURAUD:
		vertex_shader_file = "shaders\\ADSShader.vert";
		fragment_shader_file = "shaders\\ADSShader.frag";
		 break;
	case FLAT:
		vertex_shader_file = "shaders\\FlatShader.vert";
		fragment_shader_file = "shaders\\FlatShader.frag";
		break;
	case DEBUG_POS:
		vertex_shader_file = "shaders\\debug_pos_shader.vert";
		fragment_shader_file = "shaders\\debug_pos_shader.frag";
		break;
	case DEBUG_NORM:
		vertex_shader_file = "shaders\\debug_norm_shader.vert";
		fragment_shader_file = "shaders\\debug_norm_shader.frag";
	case NORM:
		vertex_shader_file = "shaders\\norm_shader.vert";
		fragment_shader_file = "shaders\\norm_shader.frag";
		break;
	case TEX:
		vertex_shader_file = "shaders\\tex_shader.vert";
		fragment_shader_file = "shaders\\tex_shader.frag";
		break;
	case TEX_W_SHADOWS:
		vertex_shader_file = "shaders\\tex_shader_w_shadows.vert";
		fragment_shader_file = "shaders\\tex_shader_w_shadows.frag";
		break;
	case TEX_NO_LIGHTING:
		vertex_shader_file = "shaders\\tex_shader.vert";
		fragment_shader_file = "shaders\\tex_no_lighting.frag";
		break;
	case GOOCH:
		vertex_shader_file = "shaders\\gooch_shader.vert";
		fragment_shader_file = "shaders\\gooch_shader.frag";
		break;
	case FIRE_NOISE:
		vertex_shader_file = "shaders\\fire_shader.vert";
		fragment_shader_file = "shaders\\fire_shader.frag";
		break;
	case NOISE_NORMAL:
		vertex_shader_file = "shaders\\noise_normal.vert";
		fragment_shader_file = "shaders\\noise_normal.frag";
		break;
	default:
		return false;
	}
	GLint gl_check;

	if (GLReturnedError("Shader::Initialize - on entrance")) return false;

	this->vertex_s_id = glCreateShader(GL_VERTEX_SHADER);
	if (!vertex_s_id)
	{
		fprintf(stderr, "Error: Could not create vertex shader %s!\n", vertex_shader_file);
		fatal_error = true;
		return false;
	}

	load(vertex_shader_file, this->vertex_s_id);
	glCompileShader(this->vertex_s_id);
	glGetShaderiv(this->vertex_s_id, GL_COMPILE_STATUS, &gl_check);

	if(gl_check != GL_TRUE)
	{
		//BUG: This does not print to console properly.
		fprintf(stderr, "GLSL compilation failed: vertex shader %s\n", vertex_shader_file);
		fprintf(stderr, "%s", this->GetShaderLog(this->vertex_s_id).str());
		fatal_error = true;
		return false;
	}

	this->frag_s_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (!frag_s_id)
	{
		fprintf(stderr, "Error: Could not create fragment shader %s!\n", fragment_shader_file);
		fatal_error = true;
		return false;
	}

	load(fragment_shader_file, this->frag_s_id);
	glCompileShader(this->frag_s_id);
	glGetShaderiv(this->frag_s_id, GL_COMPILE_STATUS, &gl_check);

	if(gl_check != GL_TRUE)
	{
		//BUG: This does not print to console properly.
		fprintf(stderr, "GLSL compilation failed: fragment shader %s\n", fragment_shader_file);
		fprintf(stderr, "%s", this->GetShaderLog(this->frag_s_id).str());
		fatal_error = true;
		return false;
	}

	this->program_id = glCreateProgram();
	if (!this->program_id)
	{
		fprintf(stderr, "Could not create shader program!\n");
		fatal_error = true;
		return false;
	}

	glAttachShader(this->program_id, this->vertex_s_id);
	glAttachShader(this->program_id, this->frag_s_id);
	
	if (GLReturnedError("Shader init - before link")) return false;

	try{
		glLinkProgram(this->program_id);
	}
	catch(int e)
	{
		fprintf(stderr, "Exception on link: %i", e);
		fatal_error = true;
		return false;
	}

	glGetProgramiv(this->program_id, GL_LINK_STATUS, &gl_check);
	if (gl_check != GL_TRUE)
	{
		fprintf(stderr, "GLSL compilation failed: could not link program\n", fragment_shader_file);
		fprintf(stderr, "%s", this->GetProgramLog(this->program_id).str());
		fatal_error = true;
		return false;
	}

	glDeleteShader(this->vertex_s_id);
	glDeleteShader(this->frag_s_id);
	
	//Are these next two lines needed?
	this->vertex_s_id = BAD_GL_VALUE;
	this->frag_s_id = BAD_GL_VALUE;
	
	this->mv_mat_handle = glGetUniformLocation(this->program_id, (const GLchar *) "mv_matrix");
	this->mvp_mat_handle = glGetUniformLocation(this->program_id, (const GLchar *) "mvp_matrix");
	this->n_mat_handle = glGetUniformLocation(this->program_id, "n_matrix");
	this->p_mat_handle = glGetUniformLocation(this->program_id, "proj_matrix");
	this->size_handle = glGetUniformLocation(this->program_id, "size");
	this->time_handle = glGetUniformLocation(this->program_id, "time");
	
	this->position_handle = glGetUniformLocation(this->program_id, "position");
	this->color_handle = glGetUniformLocation(this->program_id, "color");
	this->amb_handle = glGetUniformLocation(this->program_id, "amb");
	this->diff_handle = glGetUniformLocation(this->program_id, "diff");
	this->spec_handle = glGetUniformLocation(this->program_id, "spec");

	this->ka_handle = glGetUniformLocation(this->program_id, "kA");
	this->kd_handle = glGetUniformLocation(this->program_id, "kD");
	this->ks_handle = glGetUniformLocation(this->program_id, "kS");
	this->shininess_handle = glGetUniformLocation(this->program_id, "shininess");
	
	this->tex_handle = glGetUniformLocation(this->program_id, "Tex1");
	this->tile_handle = glGetUniformLocation(this->program_id, "tile_textures");

	subInit();

	glUseProgram(0); //Only use a shader once we call its Use function.

	if (GLReturnedError("Shader init - on exit")) return false;
	return true;
}

bool Shader::load(char * file, GLuint handle)
{
	assert(file != NULL);
	if (GLReturnedError("LoadShader - on entrance")) return false;

	FILE * f = NULL;
	fopen_s(&f, file, "rb");
	if (f == NULL)
	{
		fprintf(stderr, "Could not open shader %s\n", file);
		return false;
	}
	fseek(f, 0, FILE_END);
	int file_length = ftell(f);
	fseek(f, 0, SEEK_SET);
	GLubyte * buffer = new GLubyte[file_length + 1];
	if(fread(buffer, sizeof(GLubyte), file_length, f) != file_length)
	{
		//Why the check? Because nobody ever does it, but it breaks _everything_ when it fails.
		fprintf(stderr, "Could not read all of file %s\n", file);
		return false;
	}
	fclose(f);
	buffer[file_length] = 0; //Make sure it's null-terminated
	glShaderSource(handle, 1, (const char **) &buffer, NULL); 
	delete[] buffer;

	if (GLReturnedError("LoadShader - on exit")) return false;
	return true;
}

/*
	This function is adapted from OpenGL 4.0 Shading Language Cookbook by David Wolff.
	TODO: Cleanup; also it's not quite working.
*/
using namespace std;
stringstream Shader::GetShaderLog(GLuint shader_id)
{
	stringstream s;
	GLint log_length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length <= 0)
		s << "No shader log information available." << endl;
	else
	{
		GLchar * buffer = new GLchar[log_length];
		glGetShaderInfoLog(shader_id, log_length, NULL, buffer);
		s << "Shader log:" << endl;
		s << buffer << endl;
		delete [] buffer;
	}
	return s;
}

stringstream Shader::GetProgramLog(GLuint program_id)
{
	stringstream s;
	GLint log_length;
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length <= 0)
		s << "No program log information available." << endl;
	else
	{
		GLchar * buffer = new GLchar[log_length];
		glGetProgramInfoLog(program_id, log_length, NULL, buffer);
		s << "Program log:" << endl;
		s << buffer << endl;
		delete [] buffer;
	}
	return s;
}