#include "Cube.h"
using namespace glm;

Cube::Cube(void)
{
	this->draw_type = GL_TRIANGLES;
	super();
}


Cube::~Cube(void)
{
}

bool Cube::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Cube draw - on entry\n")) return false;
	super::s_draw(proj, mv, size, time, l, m);
#ifdef _DEBUG
	//Axes a;
	//a.init();
	//lightInfo * x = NULL;
	//a.draw(proj, glm::scale(mv, vec3(2.0, 2.0, 2.0)), size, time, x);
#endif

	if (GLReturnedError("Cube - draw exit\n")) return false;
	return true;
}

bool Cube::init(float w, float h, float d)
{
	//Positive x is left as we face the front of the cube.
	//Front face
	VertexAttPCN f_br = VertexAttPCN(vec3(0.0, 0.0, 0.0), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, -1.0));
	VertexAttPCN f_bl = VertexAttPCN(vec3(w, 0.0, 0.0), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, -1.0));
	VertexAttPCN f_ur = VertexAttPCN(vec3(0.0, h, 0.0), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, -1.0));
	VertexAttPCN f_ul = VertexAttPCN(vec3(w, h, 0.0), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, -1.0));
	
	//Back face (note this is flipped horizontally from as though we were looking at it.)
	VertexAttPCN b_br = VertexAttPCN(vec3(0.0, 0.0, d), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, 1.0));
	VertexAttPCN b_bl = VertexAttPCN(vec3(w, 0.0, d), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, 1.0));
	VertexAttPCN b_ur = VertexAttPCN(vec3(0.0, h, d), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, 1.0));
	VertexAttPCN b_ul = VertexAttPCN(vec3(w, h, d), vec3(0.5, 0.5, 0.5), vec3(0.0, 0.0, 1.0));

	//TODO: Check normals/winding. X

	//TODO: Fix winding. X

	//front
	subInit(f_br, f_ur, f_bl, f_ul, vec3(0.0, 0.0, -1.0));
	
	//top
	subInit(f_ur, b_ur, f_ul, b_ul, vec3(0.0, 1.0, 0.0));
	
	//back
	subInit(b_ur, b_br, b_ul, b_bl, vec3(0.0, 0.0, 1.0));
	
	//bottom
	subInit(b_br, f_br, b_bl, f_bl, vec3(0.0, -1.0, 0.0));

	//left
	subInit(b_br, b_ur, f_br, f_ur, vec3(-1.0, 0.0, 0.0));

	//right
	subInit(b_ul, b_bl, f_ul, f_bl, vec3(1.0, 0.0, 0.0));

	if (!this->bindArray(&this->vertex_arr_handle, &this->vertex_coor_handle, this->atts_pcn.size() * sizeof(VertexAttPCN), &this->atts_pcn[0])) return false;
	//if (!this->bindArray(&this->normal_arr_handle, &this->normal_coor_handle, this->atts_pcn.size() * sizeof(VertexAttPCN), &this->atts_pcn[0])) return false;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) (0 + sizeof(vec3) * 1)); 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCN), (GLvoid *) (0 + sizeof(vec3) * 2)); 
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//if (!this->shader.init(PHONG)) return false;
	if (GLReturnedError("Cube - init exit\n")) return false;

	return true;
}

//NOTE: WE NEED TO CONVERT BOX2D UNITS TO FEET AND VICE-VERSA
void Cube::initPhysics(float size, glm::vec2 center, float angle, b2World * world)
{
	//In 'center' here, y is z
	boxDef.type = b2_staticBody;
	boxDef.position.Set(center.x, center.y);
	boxBody = world->CreateBody(&boxDef);
	boxShape.SetAsBox(size, 1.0f, b2Vec2(center.x, center.y), angle); //TODO: Adjust angle
	boxBody->CreateFixture(&boxShape, 0.0f);
	
}


void Cube::subInit(VertexAttPCN b_l, VertexAttPCN u_l, VertexAttPCN b_r, VertexAttPCN u_r, vec3 norm)
{
	b_l.norm = u_l.norm = u_r.norm = b_r.norm = norm;
	

	this->atts_pcn.push_back(u_l);
	this->atts_pcn.push_back(u_r);
	this->atts_pcn.push_back(b_l);

	this->vertex_indices.push_back(this->atts_pcn.size() - 3);
	this->vertex_indices.push_back(this->atts_pcn.size() - 2);
	this->vertex_indices.push_back(this->atts_pcn.size() - 1);

	this->atts_pcn.push_back(b_r);
	this->atts_pcn.push_back(b_l);
	this->atts_pcn.push_back(u_r);

	this->vertex_indices.push_back(this->atts_pcn.size() - 3);
	this->vertex_indices.push_back(this->atts_pcn.size() - 2);
	this->vertex_indices.push_back(this->atts_pcn.size() - 1);
}
