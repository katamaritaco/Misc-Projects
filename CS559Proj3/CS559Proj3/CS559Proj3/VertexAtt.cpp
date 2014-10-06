#include "VertexAtt.h"

VertexAttP::VertexAttP(void)
{
	this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

VertexAttP::VertexAttP(glm::vec3 pos)
{
	this->pos = pos;
}

VertexAttP::~VertexAttP(void)
{
}

VertexAttPCN::VertexAttPCN(void)
{
	this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->norm = glm::vec3(0.0f, 0.0f, 0.0f);
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
}

VertexAttPCN::VertexAttPCN(glm::vec3 pos, glm::vec3 col, glm::vec3 norm)
{
	this->pos = pos;
	this->color = col;
	this->norm = norm;
}

void VertexAttPCN::print()
{
	printf("pos: (%f, %f, %f), col: (%f, %f, %f), norm: (%f, %f, %f)\n", this->pos.x, this->pos.y, this->pos.z, 
		this->color.x, this->color.y, this->color.z, this->norm.x, this->norm.y, this->norm.z);
}

VertexAttPCN::~VertexAttPCN(void)
{

}

VertexAttPCNT::VertexAttPCNT(void)
{
	this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->norm = glm::vec3(0.0f, 0.0f, 0.0f);
	this->color = glm::vec3(0.0f, 0.0f, 0.0f);
	this->tex_coord = glm::vec2(0.0f, 0.0f);
}

VertexAttPCNT::VertexAttPCNT(glm::vec3 pos, glm::vec3 col, glm::vec3 norm, glm::vec2 tex)
{
	this->pos = pos;
	this->color = col;
	this->norm = norm;
	this->tex_coord = tex;
}

VertexAttPCNT::~VertexAttPCNT(void)
{
}