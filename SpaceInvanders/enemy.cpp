#include "enemy.h"
#include "../sgg/include/graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "Game.h"

//dinoume tin taxitita pou kineitai o meteoritis

void Enemy::update()
{
	pos_x -= speed * graphics::getDeltaTime()*1.2f;

	if (pos_x < -50) {
		active = false;
	}

}
//dinoume tin taxitita pou kineitai to ufo 

void Enemy::updateUfo() {
	pos_x -= speed * graphics::getDeltaTime()*1.2f;

	if (pos_x < -50) {
		active = false;
	}

}

//edw emfanizetai grafika o meteoritis kai i skia tou me ta katallila assets kai to opacity. i resetPose() einai gia ton prosanatolismo tou asset.

void Enemy::draw()
{

		brush.texture = std::string(ASSET_PATH) + "asteroid.png";
		brush.fill_opacity = 0.5f;
		graphics::drawRect(pos_x - 10, pos_y + 30, size, size, brush);
		brush.texture = std::string(ASSET_PATH) + "asteroid.png";
		brush.fill_opacity = 1.0f;
		graphics::drawRect(pos_x, pos_y, size, size, brush);
		graphics::resetPose();
	

}
	//emfanizetai grafika to ufo kai i skia tou me ta katallila assets kai to opacity. i resetPose() einai gia ton prosanatolismo tou asset.	

void Enemy::drawufo() {

		brush.texture = std::string(ASSET_PATH) + "ufo.png";
		brush.fill_opacity = 0.5f;
		graphics::drawRect(pos_x - 10, pos_y + 30, size, size, brush);
		brush.texture = std::string(ASSET_PATH) + "ufo.png";
		brush.fill_opacity = 1.0f;
		graphics::drawRect(pos_x, pos_y, size, size, brush);
		graphics::resetPose();
	}

	

//arxikopoihsh tou enemy. dinetai i taxitita, i topothesia kai to megethos tou.

void Enemy::init()
{
	speed=0.3f;
	pos_x = CANVAS_WIDTH + 1.1f * size;
	pos_y = CANVAS_HEIGHT* rand0to1();
	size=50+100* rand0to1();

	brush.outline_opacity = 0.0f;
}
 //Constructor
Enemy::Enemy(const class Game & mygame)
	: gameobject(mygame)
{
	init();
}
//Destructor
Enemy::~Enemy()
{
}
//methodos pou kaleitai otan ginetai sigkrousi

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.45f;
	return disk;
}
