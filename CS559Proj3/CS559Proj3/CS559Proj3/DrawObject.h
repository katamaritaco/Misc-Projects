#pragma once
#include "glutInclude.h"
#include "Box2D\Box2D.h"
#include "VertexAtt.h"
#include <algorithm>
#include "Shader.h"
#include "ShaderWithShadows.h"

using namespace std;

extern Shader * common_shader; //Single shader used for spheres
class DrawObject
{
public:
	DrawObject(void);
	~DrawObject(void);
	bool initialize(void);
	void TakeDown(void);

	bool bindArray(GLuint * arr_handle, GLuint * coor_handle, GLsizeiptr size, const GLvoid * data);
	void UseTexture();
	void recolor(glm::vec3 color); //OBSOLETE
	void switchShader(SHADER_TYPE t); //Switches the primary shader
	inline void setShader(Shader * newShader) { shader = newShader; customShader = true; }
	inline void setTexture(TEXTURE_TYPE type) { texture = type;}
	inline void toggleTiling(bool doTile) { tile_texture = doTile; }
	inline void toggleShader(bool set) { customShader = set; }

	void setPos(glm::vec3 pos);
	inline glm::vec3 getPos() { return position; };
	inline Shader * getShader(void) { return this->shader;}
	
	static Shader norm_shader; // All objects will use the same norm shader.  
	static bool draw_norms;    // If we're showing normals, may as well show them all, since we can't much switch between objects.
	static Shader second_shader; // Unused; would have been an additional shader available for individual objects
	static bool draw_axes; // Are we drawing local axes?
	static DrawObject * a; // Shared Axes object 
	static bool axes_init; // Mark if our shared Axes object has been initialized
	static bool draw_shadows; // Mark if we're using dynamic shadows

	bool is_init; // Mark if this object is successfully initialized
protected:

	//bool GLReturnedError(char * s);
	bool initNorms(); // Sets up vertex array of normals
	void drawNorms(); // Draws normals
	bool norms_init; // Indicates normals have been 
	glm::vec3 color; // OBSOLETE: Color of the object
	bool useTex; // Indicates we're using a texture
	bool customShader; // Indicates we're using a custom shader for this object
	int draw_type; //eg. GL_TRIANGLES, GL_LINES
	bool s_draw(const glm::mat4 & proj, glm::mat4 & mv, const glm::ivec2 & size, const float & time, lightInfo * & l, materialInfo * & m); //Does the actual heavy lifting for draw

	glm::vec3 position; //Overall position in the world

	//Handles for our vertex arrays and texture
	GLuint vertex_arr_handle;
	GLuint vertex_coor_handle;
	GLuint normal_arr_handle;
	GLuint normal_coor_handle;
	GLuint tex_arr_handle;
	GLuint tex_coor_handle;
	GLuint tex_handle;

	vector<GLuint> vertex_indices;
	vector<VertexAttPCN> atts_pcn; // Stores Position/Color/Normal
	vector<VertexAttPCNT> atts_pcnt; // Stores Position/Color/Normal/Texture coords
	vector<VertexAttP> norm_vertices; // Stores vertices for drawing normals
	vector<GLuint> norm_indices;

	Shader * shader; // Custom shader for this object
	TEXTURE_TYPE texture; // Marks which texture we're using
	bool tile_texture; // Toggles tiling of texture

	glm::vec3 goochCool; //Used in gooch shading
	glm::vec3 goochWarm; //Used in gooch shading

	b2Body * physicsBody; //This will be left unused if there are no associated phsyics

	inline glm::vec4 MakeColor(int r, int g, int b, float gain = 1.0f) {	return glm::vec4(float(r) * gain / 255.0f, float(g) * gain / 255.0f, float(b) * gain / 255.0f, 1.0f); } //OBSOLETE
};

