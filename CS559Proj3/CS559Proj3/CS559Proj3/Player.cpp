#include "Player.h"
#include "glm\gtx\rotate_vector.hpp"

Player::Player(void)
{
}

Player::~Player(void)
{
}

bool Player::init(float radius, int slices, int stacks, float x, float z)
{
	//Initialization code
	glm::vec4 colors[2] = {glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)};
	sphere.setColor(colors);
	this->sphere.initialize(SPHERE_RADIUS, slices, stacks);
	this->speed = 0.01f;
	return false;
}

//Need to apply impulse to the player body
//And also adjust angle.
//Probably... adjust angle by adding to it depending on mouse location,
//Then always apply a certain forward motion.

void Player::setSpeed(float angle, float speed)
{
	//float curr_angle = this->sphere.getBody()->GetAngle();
	//curr_angle += angle;
	this->ang_force = angle;
	this->speed = speed;
}

void Player::update(void)
{
	sphere.updatePos();
	glm::vec3 center = this->sphere.getPos();
	b2Body * body = this->sphere.getBody();

	//Calculate GLM look_at as radius away from center at the angle pointed to
	float rot_angle = body->GetAngle(); //Radians
	glm::vec2 travel_force = boxToGlm(body->GetLinearVelocity());
	travel_force = glm::normalize(travel_force);
	glm::vec2 rotate_force = glm::rotate(travel_force, ang_force);
	float x_force;
	float z_force;
	
	//if(speed > 0){currDirection = true;}
	//else{currDirection = false;}


	//compensate for if its zero; crash
	if(rotate_force.y > 0){
		rotate_force.y += .00001f;
	}
	else{
		rotate_force.y -= .00001f;
	}
	if(rotate_force.x > 0){
		rotate_force.x += .00001f;
	}
	else{
		rotate_force.x -= .00001f;
	}

	
	
	if (speed > 0 && lastDirection == true){
		this->lastDirection = true;
		x_force = (this->speed + 0.0001f) * rotate_force.x;
		z_force = (this->speed + 0.0001f) * rotate_force.y;
	}
	else if (speed > 0 && lastDirection == false){
		this->lastDirection = true;
		//TODO: When speed is negative we wind up flipping direction constantly
		x_force = (this->speed + 0.0001f) * -rotate_force.x;
		z_force = (this->speed + 0.0001f) * -rotate_force.y;
	}
	else if (speed <= 0 && lastDirection == true){
		this->lastDirection = false;
		//TODO: When speed is negative we wind up flipping direction constantly
		x_force = (this->speed - 0.0001f) * rotate_force.x;
		z_force = (this->speed - 0.0001f) * rotate_force.y;
	}
		else if (speed <= 0 && lastDirection == false){
		this->lastDirection = false;
		//TODO: When speed is negative we wind up flipping direction constantly
		x_force = (this->speed - 0.0001f) * -rotate_force.x;
		z_force = (this->speed - 0.0001f) * -rotate_force.y;
	}



	body->SetLinearVelocity(b2Vec2(x_force, z_force));
	
	travel_force = glm::normalize(boxToGlm(body->GetLinearVelocity()));
	float x;
	float z;
	//printf("Angle: %f, x: %f, z: %f, radius: %f, rot_angle: %f, travel_angle: %f,\nx_force: %f, z_force: %f\n", rot_angle, x, z, sphere.getRadius(), rot_angle, x_force, z_force);
	if (this->speed > 0)
	{
		x = center.x + (sphere.getRadius() * travel_force.x);
		z = center.z + (sphere.getRadius() * travel_force.y);
		playCam.modelview = glm::lookAt(glm::vec3(x, 0.0, z), glm::vec3(x + (sphere.getRadius() * travel_force.x), 0.0, z + (sphere.getRadius() * travel_force.y)), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		x = center.x + (sphere.getRadius() * -travel_force.x);
		z = center.z + (sphere.getRadius() * -travel_force.y);
		playCam.modelview = glm::lookAt(glm::vec3(x, 0.0, z), glm::vec3(x + (sphere.getRadius() * -travel_force.x), 0.0, z + (sphere.getRadius() * -travel_force.y)), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	//player_pos = b2Vec2(x, z);
	playCam.proj = glm::perspective(playCam.fov, window.aspect, 1.0f, 20000.0f);

	//body->SetAngularVelocity(ang_force);

	/*
	if ((body->GetAngle() < PI_F/2) && (ang_force > 0))
	{
		this->sphere.getBody()->ApplyAngularImpulse(ang_force);
	}
	else if ((body->GetAngle() > -PI_F/2) && (ang_force < 0))
	{
		this->sphere.getBody()->ApplyAngularImpulse(ang_force);
	}*/
	
}

void Player::initPhysics(b2World * world)
{
	sphere.initPhysics(world);
	sphere.getBody()->ApplyLinearImpulse(b2Vec2(0.1f, 0.1f), sphere.getBody()->GetWorldCenter());
	sphere.setPlayer(true);
}

bool Player::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	return this->sphere.draw(proj, mv, size, time, l, m);
}

Camera * Player::getCam(void)
{
	return &playCam;
}
