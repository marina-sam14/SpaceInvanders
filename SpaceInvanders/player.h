#pragma once
#include "gameobject.h"
#include "config.h"
#include "enemy.h"

//pedia kai methodoi

class Player : public gameobject,public Collidable
{
	float speed = 10.0f; //pedia kai methodoi


	float life ;
	float height = 1.0f;
	

public:
	float pos_x_p = CANVAS_WIDTH / 2, pos_y_p = CANVAS_HEIGHT / 2;
	bool active = true;
	bool isActive() { return active; }

	Player(const class Game& mygame);
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
	float getPosY() { return pos_y_p; }
	float getPosX() { return pos_x_p; }
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }//zwi pou exei akoma o paiktis
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }//meiwsi zwis meta apo kathe sigkrousi me enemy
	void Setlife(float amount){ life = amount; }

};

