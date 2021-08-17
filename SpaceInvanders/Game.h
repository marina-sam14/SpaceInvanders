#pragma once
#include "player.h"
#include "enemy.h"
#include <iostream>
#include<string>

//pedia kai methodoi tis Game 

class Game {
	typedef enum{STATUS_START,STATUS_PLAYING ,STATUS_EXIT,STATUS_SCORE,STATUS_HELP,STATUS_SHOP} status_t;
	bool player_initialized = false;
	Enemy* meteorite = nullptr;
	Enemy* ufo = nullptr;
	Player* laser = nullptr;
	void spawnMeteorite();
	void spawnUfo();
	int time1 = 0;
	int money = 0;
	int shop_option = 0;
	bool bought = false;
	
	void checkMeteorite();
	void fireLaser();
	void checkUfo();
	int num=-10;
	void drawp();
	
	

	int checkCollision();
	int checkExplosion();

	status_t status=STATUS_START;

	unsigned int window_width = WINDOW_WIDTH ,
		window_height = WINDOW_HEIGHT;
	
	int xp = 0;
	void updateStartScreen();
	void updateScoreScreen();
	void updateShopScreen();
	void drawShopScreen();
	void drawScoreScreen();
	void checkLaser();
	void updateLevelScreen();
	void drawtStartScreen();
	void drawLevelScreen();
	void updateHelpScreen();
	void drawHelpScreen();
	

	int scores[10] = { 0, 0, 0, 0, 0,0,0,0,0,0 };//arxikopoihsh twn scores prin tin enarksi se 0
public:
	  //metablhth pou mas deixnei poio diasthmoploio exei dialejei o paikths
	int selected = 0;
	
	//arxikes theseis tou laser 

	int pos_x_laser = 0;
	int pos_y_laser = 0;
	float speed;

	Player* player = nullptr;
	
	float getposX() { static float px = player->getPosX(); return px; }
	float getposY() { static float py = player->getPosX(); return py; }
	
	
	

	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);


	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }

	Game();
	~Game();
};