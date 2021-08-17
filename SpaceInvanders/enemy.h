#pragma once
#include "gameobject.h"
#include "../sgg/include/graphics.h"

//pedia kai methodoi gia ton enemy

class Enemy : public gameobject, public Collidable {

	float pos_x,  pos_y;
	float speed;
	float size;
	 graphics::Brush brush;
	 bool active = true;

public:
	 
	void update() override;
	void updateUfo();
	void draw() override;
	void drawufo();
	void init() override;
	bool isActive() { return active; }
	Enemy(const class Game & mygame);
	~Enemy();

	Disk getCollisionHull() const override;



};