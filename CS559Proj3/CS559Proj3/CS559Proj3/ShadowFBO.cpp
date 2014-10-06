#include "ShadowFBO.h"


ShadowFBO::ShadowFBO(void)
{
}


ShadowFBO::~ShadowFBO(void)
{
}

//Much of the code below is adapted from the OpenGL cookbook.  TODO: PROPER AUTHOR INFOs
void ShadowFBO::initialize(void)
{
	GLfloat border[] = {1.0, 0.0, 0.0, 0.0}; //Border color for the depth map
	this->color_attachments = 1;
	this->tex_res = glm::ivec2(SHADOW_BUFFER_RES, SHADOW_BUFFER_RES);
	this->tex_handles = new GLuint[color_attachments];

	//Set up faux texture to store depth info in
	glGenTextures(1, this->tex_handles);
	glBindTexture(GL_TEXTURE_2D, tex_handles[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, tex_res.x, tex_res.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); //Disallow wrapping around the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE); //Lets us do comparisons with the depth map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	

	//Set up framebuffer
	glGenFramebuffers(1, &this->frame_buffer_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_handle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex_handles[0], 0);

	GLenum drawBuffers[]={GL_NONE}; //??????
	glDrawBuffers(1,drawBuffers);

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stderr, "FrameBufferObject: failed to set up texture buffer %s\n", FramebufferCompletenessError(status));
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}