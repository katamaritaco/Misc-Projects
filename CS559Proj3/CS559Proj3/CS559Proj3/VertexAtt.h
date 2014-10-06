#pragma once
#include "glutInclude.h"

class VertexAttP
{
public:
	VertexAttP(void);
	VertexAttP::VertexAttP(glm::vec3 pos);
	~VertexAttP(void);
	void print(void);
	glm::vec3 pos;
};


//For now, we assume we're going to keep the normal for our vertices no matter what.
//A possible future optimization would be to only calculate/store normals if we're viewing them.
class VertexAttPCN
{
public:
	VertexAttPCN(void);
	VertexAttPCN::VertexAttPCN(glm::vec3 pos, glm::vec3 col, glm::vec3 norm);
	~VertexAttPCN(void);
	void print(void);
	glm::vec3 pos;
	glm::vec3 color; //vec3 or vec4?
	glm::vec3 norm;
};


class VertexAttPCNT
{
public:
	VertexAttPCNT(void);
	VertexAttPCNT(glm::vec3 pos, glm::vec3 col, glm::vec3 norm, glm::vec2 tex);
	~VertexAttPCNT(void);
	glm::vec3 pos;
	glm::vec3 color; //vec3 or vec4?
	glm::vec3 norm;
	glm::vec2 tex_coord;
};

