#pragma once
#include "glutInclude.h"
#include "Textures.h"
class FrameBufferObject
{
public:
	FrameBufferObject(void);
	~FrameBufferObject(void);

	bool initialize(glm::ivec2 tex_res, int color_attachments, bool depth_buffer);
	void TakeDown();
	void bind(int color_attachment_index);
	void unbind(void);

protected:
	glm::ivec2 tex_res;
	GLuint * tex_handles;
	GLuint depth_buffer_handle;
	GLuint color_attachments;
	GLuint frame_buffer_handle;
};

