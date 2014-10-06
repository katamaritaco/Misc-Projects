#include "Axes.h"

using namespace glm;
Axes::Axes(void)
{
	this->shader = new Shader();
}


Axes::~Axes(void)
{
	free(this->shader);
}

bool Axes::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l)
{
	if (GLReturnedError("Axes draw - on exit\n")) return false;
	glDisable(GL_LIGHTING); //TODO: Is this correct?
	materialInfo * m = NULL;
	DrawObject::s_draw(proj, mv, size, time, l, m);
	glEnable(GL_LIGHTING);
	if (GLReturnedError("Axes draw - on exit\n")) return false;
	return true;
}

bool Axes::init(void)
{
	this->draw_type = GL_LINES;
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	VertexAttPCN origin_x, x, origin_y, y, origin_z, z;
	origin_x.pos = origin_y.pos = origin_z.pos = vec3(0.0, 0.0, 0.0);
	x.color = origin_x.color = vec3(1.0, 0.0, 0.0);
	x.pos = vec3(100.0, 0.0, 0.0);
	y.color = origin_y.color = vec3(0.0, 1.0, 0.0);
	y.pos = vec3(0.0, 100.0, 0.0);
	z.color = origin_z.color = vec3(0.0, 0.0, 1.0);
	z.color = vec3(1.0, 1.0, 1.0);
	z.pos = vec3(0.0, 0.0, 100.0);
	this->atts_pcn.push_back(origin_x);
	this->atts_pcn.push_back(x);
	this->atts_pcn.push_back(origin_y);
	this->atts_pcn.push_back(y);
	this->atts_pcn.push_back(origin_z);
	this->atts_pcn.push_back(z);
	for (int i = 0; i < 6; i++)
	{
		this->vertex_indices.push_back(i);
	}

	if (!this->bindArray(&this->vertex_arr_handle, &this->vertex_coor_handle, this->atts_pcn.size() * sizeof(VertexAttPCN), &this->atts_pcn[0])) return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), 0); //position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (const GLvoid *) (sizeof(VertexAttPCN) * 1));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
	
	//We don't need shaders for the axes!
	//Wait, yes we do! For those colors! It's just a pass-through though
	if (!(shader->init(NONE))) return false;
	this->customShader = true;
	if (GLReturnedError("Axes init - on exit\n")) return false;
	return true;

}