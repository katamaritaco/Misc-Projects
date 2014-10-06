#include "Jumbotron.h"


Jumbotron::Jumbotron(void)
{
}


Jumbotron::~Jumbotron(void)
{
}

#define SCREEN_LENGTH 600.0f
#define SCREEN_HEIGHT 300.0f

void Jumbotron::init(glm::vec3 pos, bool flipped)
{
	screenShader = new Shader();
	screenShader->init(TEX);
	if (!flipped)
	{
		stand.init(20.0f, 100.0f, 20.0f);
		stand.setPos(pos);
		stand.setTexture(CONCRETE);

		screen.init(6.5f, SCREEN_HEIGHT, SCREEN_LENGTH);
		screen.setPos(glm::vec3(pos.x - 20.1f, pos.y + 80, pos.z - SCREEN_LENGTH/2));
		screen.setTexture(FRAME_BUF);
		screen.setShader(screenShader);
	}
	else
	{
		stand.init(-20.0f, 100.0f, -20.0f);
		stand.setPos(pos);
		stand.setTexture(CONCRETE);

		screen.init(6.5f, SCREEN_HEIGHT, -SCREEN_LENGTH);
		screen.setPos(glm::vec3(pos.x + 20.1f, pos.y + 80, pos.z - SCREEN_LENGTH/2));
		screen.setTexture(FRAME_BUF);
		screen.setShader(screenShader);
	}
}

void Jumbotron::TakeDown(void)
{
	stand.TakeDown();
	screen.TakeDown();
}

bool Jumbotron::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Jumbotron draw - on entry")) return false;
	stand.draw(proj, mv, size, time, l, m);
	//if (render_target != RENDER_GOOCH)
	//{
		screen.draw(proj, mv, size, time, l, m);
	//}
	if (GLReturnedError("Jumbotron draw - on exit")) return false;
	return true;
}