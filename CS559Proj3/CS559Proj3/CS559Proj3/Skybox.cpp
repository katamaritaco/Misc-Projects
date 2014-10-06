/*	
	Code based upon code provided by Perry Kivolowitz, some code it directly copied
*/

#include <iostream>
#include "Skybox.h"

using namespace std;
using namespace glm;

Skybox::Skybox()
{
	this->draw_type = GL_TRIANGLES;
	super();
	vec4 lighter_color(MakeColor(255, 69, 0, 1.0f));
	vec4 darker_color = vec4(vec3(lighter_color) * 2.0f / 3.0f, 1.0f);
	this->colors[0] = darker_color;
	this->colors[1] = lighter_color;
	color = vec3(colors[0]);
	solidColor = false;
}

Skybox::~Skybox()
{
	//Should call TakeDown, not this!
}

inline int ColorIndex(int i, int slices)
{
	return (i / (slices / 4)) % 2;
}

inline int PreviousSlice(int i, int slices)
{
	return (i == 0) ? slices - 1 : i - 1;
}

void Skybox::BuildNormalVisualizationGeometry()
{
		//We do normals in DrawObject
	/*
	const float normal_scalar = 0.125f;
	for (int j = 1; j <= 3; ++j)
	{
		this->norm_vertices.push_back(VertexAttP(this->atts_pcn[this->atts_pcn.size() - j].position));
		this->norm_vertices.push_back(VertexAttP(this->atts_pcn[this->atts_pcn.size() - j].position + this->atts_pcn[this->atts_pcn.size() - j].normal * normal_scalar));
		this->norm_indices.push_back(this->norm_vertices.size() - 2);
		this->norm_indices.push_back(this->norm_vertices.size() - 1);
	}
	*/
}

bool Skybox::initialize(float radius, int slices, int stacks)
{
	if (GLReturnedError("Sphere::Initialize - on entry"))
		return false;

	if (!super::initialize())
		return false;

	if (slices < 0)
		slices = 1;

	slices *= 4;
	own_radius = radius;

	float theta = 360.0f/slices;
	float delta = 180.0f/stacks;
	const vec3 y_axis(0.0f, 1.0f, 0.0f);
	const vec3 z_axis(0.0f, 0.0f, 1.0f);
	const vec4 r_vec(radius, 0.0f, 0.0f, 1.0f);
	vec3 n2;
	vec4 n;
	mat4 tmpM2;
	
	mat4 m, m_nxt, m2, m2_nxt;
	for( int j=0; j<slices; j++)
	{
		m_nxt = rotate(m, theta, y_axis);
		m2 = mat4();	
		m2_nxt = rotate(mat4(), -90.0f, z_axis);
		for(int i=0; i<stacks; i++)
		{
			m2 = m2_nxt;
			m2_nxt = rotate(m2, delta, z_axis);

			//Code for generating texture coords on a sphere taken from http://www.mvps.org/directx/articles/spheremap.htm
			//However, we use opposite values for x and y than suggested so that our texture is not flipped
			//(as we're seeing the 'inside' of the sphere)
			VertexAttPCNT cur_vertex_top, cur_vertex_bottom , nxt_vertex_top,nxt_vertex_bottom;
			cur_vertex_top.pos = vec3((m*m2)*r_vec);	
			cur_vertex_top.norm = normalize(-cur_vertex_top.pos);
			cur_vertex_top.tex_coord.y = asin(cur_vertex_top.norm.x)/PI_F + 0.5f;
			cur_vertex_top.tex_coord.x = asin(cur_vertex_top.norm.y)/PI_F + 0.5f;

			nxt_vertex_top.pos = vec3((m_nxt*m2)*r_vec);	
			nxt_vertex_top.norm = normalize(-nxt_vertex_top.pos);
			nxt_vertex_top.tex_coord.y = asin(nxt_vertex_top.norm.x)/PI_F + 0.5f;
			nxt_vertex_top.tex_coord.x = asin(nxt_vertex_top.norm.y)/PI_F + 0.5f;

			cur_vertex_bottom.pos = vec3((m*m2_nxt)*r_vec);	
			cur_vertex_bottom.norm = normalize(-cur_vertex_bottom.pos);
			cur_vertex_bottom.tex_coord.y = asin(cur_vertex_bottom.norm.x)/PI_F + 0.5f;
			cur_vertex_bottom.tex_coord.x = asin(cur_vertex_bottom.norm.y)/PI_F + 0.5f;

			nxt_vertex_bottom.pos = vec3((m_nxt*m2_nxt)*r_vec);	
			nxt_vertex_bottom.norm = normalize(-nxt_vertex_bottom.pos);
			nxt_vertex_bottom.tex_coord.y = asin(nxt_vertex_bottom.norm.x)/PI_F + 0.5f;
			nxt_vertex_bottom.tex_coord.x = asin(nxt_vertex_bottom.norm.y)/PI_F + 0.5f;


			if(solidColor)
			{
				cur_vertex_bottom.color = color;
				cur_vertex_top.color = color;
				nxt_vertex_bottom.color = color;
				nxt_vertex_top.color = color;
			}
			else
			{
				cur_vertex_bottom.color = vec3(this->colors[ColorIndex(j, slices)]);
				cur_vertex_top.color = vec3(this->colors[ColorIndex(j, slices)]);
				nxt_vertex_bottom.color = vec3(this->colors[ColorIndex(j, slices)]);
				nxt_vertex_top.color = vec3(this->colors[ColorIndex(j, slices)]);
			}

			this->atts_pcnt.push_back(cur_vertex_top);
			this->atts_pcnt.push_back(cur_vertex_bottom);
			this->atts_pcnt.push_back(nxt_vertex_bottom);
	
			this->vertex_indices.push_back(this->atts_pcnt.size() - 1);
			this->vertex_indices.push_back(this->atts_pcnt.size() - 3);
			this->vertex_indices.push_back(this->atts_pcnt.size() - 2);

			this->BuildNormalVisualizationGeometry();

			this->atts_pcnt.push_back(cur_vertex_top);
			this->atts_pcnt.push_back(nxt_vertex_bottom);
			this->atts_pcnt.push_back(nxt_vertex_top);
	
			this->vertex_indices.push_back(this->atts_pcnt.size() - 1);
			this->vertex_indices.push_back(this->atts_pcnt.size() - 3);
			this->vertex_indices.push_back(this->atts_pcnt.size() - 2);

			this->BuildNormalVisualizationGeometry();
		}
		m = m_nxt;
	}



	if (!this->bindArray(&this->vertex_arr_handle, &this->vertex_coor_handle, this->atts_pcnt.size() * sizeof(VertexAttPCNT), &this->atts_pcnt[0]))
		return false;

	/*	The VertexAttributesPCN class stores vertex attributes: position, color and normal in that order.

		Vertex attributes are stored in an interleaved manner aiding speed of vertex processing.
	*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCNT), (GLvoid *) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCNT), (GLvoid *) (sizeof(vec3) * 2));	// Note offset - legacy of older code
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCNT), (GLvoid *) (sizeof(vec3) * 1));	// Same
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttPCNT), (GLvoid *) (sizeof(vec3) * 3));	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*
	We do normals in DrawObject

	if (this->norm_vertices.size() > 0)
	{
		if (!this->PostGLInitialize(&this->normal_array_handle, &this->normal_coordinate_handle, this->norm_vertices.size() * sizeof(VertexAttributesP), &this->norm_vertices[0]))
			return false;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributesP), (GLvoid *) 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}*/

	//Default with SKY
	this->texture = SKY;

	if (GLReturnedError("Sphere::Initialize - on exit"))
		return false;

	return true;
}


/* TakeDown is also handled by DrawObject
void Sphere::TakeDown()
{
	this->atts_pcn.clear();
	this->shader.TakeDown();
	this->solid_color.TakeDown();
	super::TakeDown();
}*/

/*
void Sphere::Draw(const ivec2 & size)
{
	assert(false);
}*/

/*	A note about drawing the normals.

	If you scale this object non-uniformly, drawing the normals will
	not be correct. This is because the normals are being stored for
	visualization as geometry. As such, scaling will not be corrected
	by the normal matrix.
*/

/*	A note about the index arrays.
 
	In this example, the index arrays are unsigned ints. If you know
	for certain that the number of vertices will be small enough, you
	can change the index array type to shorts or bytes. This will have
	the two fold benefit of using less storage and transferring fewer
	bytes.
*/

bool Skybox::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Sphere draw - on entry\n")) return false;

	super::s_draw(proj, mv, size, time, l, m);
#ifdef _DEBUG
	//Axes a;
	//a.init();
	//lightInfo * x = NULL;
	//a.draw(proj, glm::scale(mv, vec3(2.0, 2.0, 2.0)), size, time, x);
#endif

	if (GLReturnedError("Sphere - draw exit\n")) return false;
	return true;
}

//void Skybox::makeSkydome(void)
//{
//	//Notice: This should be called on a large sphere that does _not_ have physics associated with it.
//	//for (unsigned int i = 0; i < atts_pcnt.size(); i++)
//	//{
//	//	atts_pcnt.at(i).norm.x = -atts_pcnt.at(i).norm.x;
//	//	atts_pcnt.at(i).norm.y = -atts_pcnt.at(i).norm.y;
//	//	atts_pcnt.at(i).norm.z = -atts_pcnt.at(i).norm.z;
//	//}
//	this->texture = SKY;
//}

//void Sphere::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size)
//{
//	if (this->GLReturnedError("Sphere::Draw - on entry"))
//		return;
//	glEnable(GL_CULL_FACE); 
////	glDisable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//	mat4 mvp = projection * modelview;
//	mat3 nm = inverse(transpose(mat3(modelview)));
//
//	shader.Use();
//	shader.CommonSetup(0.0f, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm), value_ptr(worldModelView));
//	glBindVertexArray(this->vertex_array_handle);
//	glDrawElements(GL_TRIANGLES , this->vertex_indices.size(), GL_UNSIGNED_INT , &this->vertex_indices[0]);
//	glBindVertexArray(0);
//	glUseProgram(0);
//
//	if (this->draw_normals)
//	{
//		this->solid_color.Use();
//		this->solid_color.CommonSetup(0.0f, value_ptr(size), value_ptr(projection), value_ptr(modelview), value_ptr(mvp), value_ptr(nm), value_ptr(worldModelView));
//		glBindVertexArray(this->normal_array_handle);
//		glDrawElements(GL_LINES , this->norm_indices.size(), GL_UNSIGNED_INT , &this->norm_indices[0]);
//		glBindVertexArray(0);
//		glUseProgram(0);
//	}
//	
//	glDisable(GL_CULL_FACE);
//
//	if (this->GLReturnedError("Sphere::Draw - on exit"))
//		return;
//}
