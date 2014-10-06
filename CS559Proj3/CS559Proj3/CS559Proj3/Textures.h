#pragma once
#include "MaterialInfo.h"
enum TEXTURE_TYPE {DIRT, CONCRETE, SKY, NIGHT_SKY, TEXTTEST, FRAME_BUF, SHADOW_BUF, NOISE, TEX_ERR};
static const int NUM_TEXTS = 5; //Number of textures we load from external sources
//"dirt.jpg", "concrete.jpg" from http://seamless-pixels.blogspot.com/
//"nightsky.jpg" from http://loadpaper.com
//"sky.jpg" from http://texturez.com
//"texttest.jpg" just a "Hello, world!"
static const char * texts[NUM_TEXTS] = {"dirt.jpg", "concrete.jpg", "sky.jpg", "nightsky.jpg", "texttest.jpg"};

struct skyboxInfo
{
	lightInfo l;
	TEXTURE_TYPE tex;
};