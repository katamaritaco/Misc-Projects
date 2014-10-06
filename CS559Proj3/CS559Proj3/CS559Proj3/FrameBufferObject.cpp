#include "FrameBufferObject.h"
//Much of this class is based on the example provided by Perry Kivolowitz.


FrameBufferObject::FrameBufferObject(void)
{
}


FrameBufferObject::~FrameBufferObject(void)
{
}

void FrameBufferObject::bind(int color_attachment_index)
{
	if (GLReturnedError("FrameBufferObject - bind entry\n"))
	{
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_handle);
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + color_attachment_index);
}

void FrameBufferObject::unbind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool FrameBufferObject::initialize(glm::ivec2 tex_res, int color_attachments, bool depth_buffer)
{
	this->color_attachments = color_attachments;
	this->tex_res = tex_res;
	this->tex_handles = new GLuint[color_attachments];

	for (int i = 0; i < color_attachments; i++)
	{
		tex_handles[i] = GLuint(-1);
	}

	if (GLReturnedError("FrameBufferObject - init entry\n"))
	{
		return false;
	}

	glGenFramebuffers(1, &this->frame_buffer_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_handle);
	
	if (GLReturnedError("FrameBufferObject - after binding framebuffer\n"))
	{
		return false;
	}

	for (int i = 0; i < color_attachments; i++)
	{
		//TODO: Check if we need to account for GLActiveTexture
		glBindTexture(GL_TEXTURE_2D, this->tex_handles[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tex_res.x, tex_res.y, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //TODO: What exactly does this line do?
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, this->tex_handles[i], 0);
	}

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stderr, "FrameBufferObject: failed to set up texture buffer %s\n", FramebufferCompletenessError(status));
		return false;
	}

	if(depth_buffer)
	{
		glGenRenderbuffers(1, &this->depth_buffer_handle);
		glBindRenderbuffer(GL_RENDERBUFFER, this->depth_buffer_handle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->tex_res.x, this->tex_res.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depth_buffer_handle);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stderr, "FrameBufferObject: failed to set up texture buffer %s\n", FramebufferCompletenessError(status));
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void FrameBufferObject::TakeDown(void)
{
	if (this->frame_buffer_handle != GLuint(-1))
	{
		glDeleteFramebuffers(1, &this->frame_buffer_handle);
	}
	if (this->depth_buffer_handle != GLuint(-1))
	{
		glDeleteRenderbuffers(1, &this->depth_buffer_handle);
	}
	if (tex_handles != NULL)
	{
		glDeleteTextures(this->color_attachments, this->tex_handles);
		delete [] tex_handles;
	}
}