#pragma once
#include "framebufferobject.h"
#define SHADOW_BUFFER_RES 2048

//The ShadowFBO class is a slightly modified FrameBufferObject that records depth information for generating shadow maps.

class ShadowFBO :
	public FrameBufferObject
{
public:
	ShadowFBO(void);
	~ShadowFBO(void);
	void initialize(void);
};

