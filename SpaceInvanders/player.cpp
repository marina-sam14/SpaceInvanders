#include "player.h"
#include "../sgg/include/graphics.h"
#include "Game.h"


Player::Player(const Game& mygame)
	: gameobject(mygame)
{
}

//kinisi diastimoploiou

void Player::update()
{


	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		pos_x_p -= speed * graphics::getDeltaTime() / 10.0f;
		
	}if (graphics::getKeyState(graphics::SCANCODE_D)) {
		pos_x_p += speed * graphics::getDeltaTime() / 10.0f;

	}if (graphics::getKeyState(graphics::SCANCODE_W)) {
		pos_y_p -= speed * graphics::getDeltaTime() / 10.0f;

	}if (graphics::getKeyState(graphics::SCANCODE_S)) {
		pos_y_p += speed * graphics::getDeltaTime() / 10.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		height -= 0.01f * graphics::getDeltaTime();
		if (height < 3.0f)
			height = 3.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		height += 0.01f * graphics::getDeltaTime();
		if (height < 0.1f)
			height = 0.1f;
	}


	if (pos_x_p < 0)pos_x_p = 0;
	if (pos_x_p > CANVAS_WIDTH)pos_x_p = CANVAS_WIDTH;
	if (pos_y_p < 0)pos_y_p = 0;
	if (pos_y_p > CANVAS_HEIGHT)pos_y_p = CANVAS_HEIGHT;



}

void Player::draw()
{
	
}

void Player::init()
{
}
//sigkrousi

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x_p;
	disk.cy = pos_y_p;
	disk.radius = 55.0f;
	return disk;
}
