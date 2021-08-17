#include "Game.h"
#include "../sgg/include/graphics.h"
#include "config.h"
#include <stdlib.h>

//elegxoume an iparxei meteoritis kai an den iparxei, kataskeuazoyme emeis 

void Game::spawnMeteorite()
{ 
	
	if (!meteorite) {
		meteorite = new Enemy(*this);
		num += 10;
	}

}

//elegxoume an iparxei meteoritis kai an den iparxei, kataskeuazoyme emeis
void Game::spawnUfo()
{

	if (!ufo) {
		ufo = new Enemy(*this);
		num += 5;
		
	}

}



//an iparxei meteoritis alla den einai active, katastrefetai

void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive()) {
		delete meteorite;
		meteorite = nullptr;
	}
}



//dimiourgoyme grafika to laser pou pirovolei o paiktis tous extrous. i topotheisa tou laser einai i idia me tous paikti kai xrisimopoioume
 
void Game::fireLaser()
{
	

		
		graphics::playSound(std::string(ASSET_PATH) + "pew.mp3", 0.5f, false);//stigmiaios ixos pou akougetai kata ton pirovolismo

		pos_x_laser = player->getPosX();
		pos_y_laser = player->getPosY();
		graphics::Brush brush;
		
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);

		brush.texture = "";
		brush.fill_color[0] = 1.0f;
		brush.fill_color[1] = 0.5f + glow * 0.5f;
		brush.fill_color[2] = 0.0f;
		brush.fill_secondary_color[0] = 0.3f;
		brush.fill_secondary_color[1] = 0.1f;
		brush.fill_secondary_color[2] = 0.0f;
		brush.fill_opacity = 1.0f;
		brush.fill_secondary_opacity = 0.0f;
		brush.gradient = true;
		graphics::setScale(0.3f, 0.3f);
		graphics:drawRect(pos_x_laser+650, pos_y_laser,4000 ,20, brush);
		graphics::resetPose();
		
}

//an iparxei ufo alla den einai active, katastrefetai

void Game::checkUfo()
{
	if (ufo && !ufo->isActive()) {
		delete ufo;
		ufo = nullptr;
	}
}

//dimiourgeitai grafika to diastimoploio me katallila assets kai xrwmata. dinetai i topothesia tou kai o prosanatolismos tou. 

void Game::drawp()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	
	graphics::setOrientation(-90.f);
	graphics::setScale(1.0f, 1.0f);
	br.fill_opacity = 0.1f;
	if (selected == 0)
		br.texture = std::string(ASSET_PATH) + "spaceship.png";
	else
		br.texture = std::string(ASSET_PATH) + "spaceship2.png";

	graphics::drawRect(player->getPosX() - 10 * 1.0f, player->getPosX() + 30 * 3 * 1.0f, 100, 100, br);

	br.fill_opacity = 1.0f;
	if (selected == 0)
		br.texture = std::string(ASSET_PATH) + "spaceship.png";
	else
		br.texture = std::string(ASSET_PATH) + "spaceship2.png";

	graphics::drawRect(player->getPosX(), player->getPosY(), 100, 100, br);
	graphics::resetPose();

	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(1.0f, 1.0f);
graphics:drawDisk(player->getPosX() - 50 * 1.0f, player->getPosY(), 20, br);
	graphics::resetPose();
}

//tsekarei an uparxei sugkroush metaju tou diasthmoploiou kai ufo h komhth
int Game::checkCollision()
{
	if (!player || !meteorite||!ufo ) {
		return 0;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = meteorite->getCollisionHull();
	
		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;



		if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
			player->drainLife(0.2f);
			graphics::playSound(std::string(ASSET_PATH) + "beep.mp3", 0.5f, false);
			num -= 5;
			return 1;
		}
		else
		
		d1 = player->getCollisionHull();
		d2 = ufo->getCollisionHull();

		 dx = d1.cx - d2.cx;
		 dy = d1.cy - d2.cy;



		if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
			player->drainLife(0.1f);
			graphics::playSound(std::string(ASSET_PATH) + "beep.mp3", 0.5f, false);
			num -= 10;
			return 2;
		}
		else
		{
			return 0;
		}
	}

//methodos pou elegxei an to laser petixe ton enemy. an ton petixei, pairnei tous antistoixous vathmous. 10 gia ton meteoriti kai 20 gia to ufo.

int Game::checkExplosion()
{

	if (!laser || !meteorite||!ufo) {
		return 0;
	}


	Disk d2 = meteorite->getCollisionHull();


	if (d2.cy > pos_y_laser - 30 && d2.cy < pos_y_laser + 30&& d2.cx>pos_x_laser) {
		num+=10;
		
		return 1;
	}
	

	 d2 = ufo->getCollisionHull();
	 
	if (d2.cy > pos_y_laser-30&& d2.cy < pos_y_laser + 30&&d2.cx>pos_x_laser) {
		num += 20;

		return 2;
	}
	else { return 0; }
}
	

//Mouse-Menu gia ton paikti wste na mporei na paiksei,na deis ta scores tou,na agorasei nees emfaniseis kai na vgei ekso apo to paixnidi.

void Game::updateStartScreen()
{
	

		//button.mp3-> stigmiaios ixos pontikiou kata to klik mias epilogis


	graphics::MouseState ms; 
	graphics::getMouseState(ms);
	
	if (ms.button_left_pressed) {
		if (ms.cur_pos_x > 95 && ms.cur_pos_x < 195 && ms.cur_pos_y>140 && ms.cur_pos_y < 200) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);

			status = STATUS_PLAYING;
		}
		else if (ms.cur_pos_x > 95 && ms.cur_pos_x < 230 && ms.cur_pos_y>230 && ms.cur_pos_y < 275) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);

			status = STATUS_SCORE;
		}
		else if (ms.cur_pos_x > 95 && ms.cur_pos_x < 195 && ms.cur_pos_y>305 && ms.cur_pos_y < 360) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);

			status = STATUS_HELP;
		}
		else if (ms.cur_pos_x > 95 && ms.cur_pos_x < 195 && ms.cur_pos_y>400 && ms.cur_pos_y < 450) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);

			status = STATUS_SHOP;
		}
		else if (ms.cur_pos_x > 95 && ms.cur_pos_x < 195 && ms.cur_pos_y>470 && ms.cur_pos_y < 540) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);

			status = STATUS_EXIT;
		}
	}
}
//UI gia tin epilogi High Scores tou Menu

void Game::updateScoreScreen()
{




	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed && ms.cur_pos_x>840 && ms.cur_pos_x<1100 && ms.cur_pos_y>0 && ms.cur_pos_y<220 ) {
		graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


			status = STATUS_START;

	}
}
//UI gia tin agora kapoiou asset apo to Shop tou Menu

void Game::updateShopScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed && ms.cur_pos_x > 840 && ms.cur_pos_x < 1100 && ms.cur_pos_y>0 && ms.cur_pos_y < 120) {
		graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


		status = STATUS_START;

	}

	if (shop_option == 0) {
		if (ms.button_left_pressed && ms.cur_pos_x > 680 && ms.cur_pos_x < 880 && ms.cur_pos_y>230 && ms.cur_pos_y < 320) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


			shop_option++;

		}
		else if (selected == 1) {
			if (ms.button_left_pressed && ms.cur_pos_x > 500 && ms.cur_pos_x < 610 && ms.cur_pos_y>460 && ms.cur_pos_y < 520) {
				graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


				selected = 0;
			}
		}
	}

	else if (shop_option == 1) {
		if (ms.button_left_pressed && ms.cur_pos_x > 280 && ms.cur_pos_x < 400 && ms.cur_pos_y>230 && ms.cur_pos_y < 320) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


			shop_option--;
		}
		else if (ms.button_left_pressed && ms.cur_pos_x > 500 && ms.cur_pos_x < 610 && ms.cur_pos_y>460 && ms.cur_pos_y < 520) {
			graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);
			if (bought==false){
				if (money >= 500) {
					money -= 500;
					bought = true;
					selected = 1;
				}
			}else if (selected==0){
				if (ms.button_left_pressed && ms.cur_pos_x > 500 && ms.cur_pos_x < 610 && ms.cur_pos_y>460 && ms.cur_pos_y < 520) {
					graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


					selected = 1;
				}
			}
			
		}

	}
	
}
//UI gia to shop 

void Game::drawShopScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "shop-back.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH , CANVAS_HEIGHT , br);

	char info[40];
	sprintf_s(info, "BACK");
	graphics::drawText(850, 50, 30, info, br);

	std::string str2 = "MONEY:";
	str2 += std::to_string(money);
	str2 += "$";
	graphics::drawText(100, 30, 45, str2, br);
	if (bought == false) {
		if (shop_option == 0) {
			br.fill_opacity = 1.0f;
			br.texture = std::string(ASSET_PATH) + "spaceship.png";
			graphics::drawRect(500, 250, 300, 200, br);

			char info1[40];
			sprintf_s(info1, "ALREADY  BOUGHT");
			graphics::drawText(410, 420, 30, info1, br);

			br.fill_opacity = 1.0f;
			br.texture = std::string(ASSET_PATH) + "arrow.png";
			graphics::drawRect(700, 250, 50, 50, br);
		}
		else if (shop_option == 1) {
			br.fill_opacity = 1.0f;
			br.texture = std::string(ASSET_PATH) + "spaceship2.png";
			graphics::drawRect(500, 250, 300, 200, br);

			char info2[40];
			sprintf_s(info2, "BUY:500$");
			graphics::drawText(435, 420, 30, info2, br);

			br.fill_opacity = 1.0f;
			graphics::setOrientation(180);
			br.texture = std::string(ASSET_PATH) + "arrow.png";

			graphics::drawRect(300, 250, 50, 50, br);
			graphics::resetPose();
		}
	}
	else {
		if (selected == 0) {
			if (shop_option == 0) {
				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "spaceship.png";
				graphics::drawRect(500, 250, 300, 200, br);

				char info1[40];
				sprintf_s(info1, "SELECTED");
				graphics::drawText(435, 420, 30, info1, br);

				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "arrow.png";
				graphics::drawRect(700, 250, 50, 50, br);
			}
			else if (shop_option == 1) {
				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "spaceship2.png";
				graphics::drawRect(500, 250, 300, 200, br);

				char info2[40];
				sprintf_s(info2, "SELECT");
				graphics::drawText(435, 420, 30, info2, br);

				br.fill_opacity = 1.0f;
				graphics::setOrientation(180);
				br.texture = std::string(ASSET_PATH) + "arrow.png";

				graphics::drawRect(300, 250, 50, 50, br);
				graphics::resetPose();
			}
		}else{
			if (shop_option == 0) {
				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "spaceship.png";
				graphics::drawRect(500, 250, 300, 200, br);

				char info1[40];
				sprintf_s(info1, "SELECT");
				graphics::drawText(435, 420, 30, info1, br);

				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "arrow.png";
				graphics::drawRect(700, 250, 50, 50, br);
			}
			else if (shop_option == 1) {
				br.fill_opacity = 1.0f;
				br.texture = std::string(ASSET_PATH) + "spaceship2.png";
				graphics::drawRect(500, 250, 300, 200, br);

				char info2[40];
				sprintf_s(info2, "SELECTED");
				graphics::drawText(435, 420, 30, info2, br);

				br.fill_opacity = 1.0f;
				graphics::setOrientation(180);
				br.texture = std::string(ASSET_PATH) + "arrow.png";

				graphics::drawRect(300, 250, 50, 50, br);
				graphics::resetPose();
			}
		}

	}
	
}
//UI gia ta High Scores. 

void Game::drawScoreScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "score.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char info4[40];
	sprintf_s(info4, "BACK");
	graphics::drawText(850, 50, 30, info4, br);

	

	int xprint = 310;
	int yprint = 200;
	int g = 0;
	for (int k = 9; k >= 0; k--) {
		 g++;
		 if (k == 4) { xprint = 655; yprint = 200; }
		std::string str = std::to_string(g);
		str += ".  ";
		std::string str1 = std::to_string(scores[k]);
		str += str1;
		graphics::drawText(xprint, yprint, 35, str, br);
		yprint += 50;
	}



	

}

//Xrisi tis partition tis Quicksort gia taksinomisi tou scores 

int partition(int* a, int start, int end)
{
	int pivot = a[end];

	int P_index = start;
	int i, t; 

	
	for (i = start; i < end; i++)
	{
		if (a[i] <= pivot)
		{
			t = a[i];
			a[i] = a[P_index];
			a[P_index] = t;
			P_index++;
		}
	}
	
	t = a[end];
	a[end] = a[P_index];
	a[P_index] = t;

	return P_index;
}
//Quicksort 

void Quicksort(int* a, int start, int end)
{
	if (start < end)
	{
		int P_index = partition(a, start, end);
		Quicksort(a, start, P_index - 1);
		Quicksort(a, P_index + 1, end);
	}
}
//an den iparxei laser, to dimiourgoume kai kaloume tin fireLaser i opoia einai auti pou ektokseuei ta pyra

void Game::checkLaser() {
	if (!laser && graphics::getKeyState(graphics::SCANCODE_Q)) {
		laser = new Player(*this);
		laser->active = true;
		fireLaser(); }
}

/*dimiourgia paikti kai exthrou. arxikopoihsh tou score,tis zwis kai twn xrimatwn pou pairnei o paiktis me tis epidoseis tou. 
akoma kalountai oi methodoi gia sigkrouseis kai pirovolismous*/
void Game::updateLevelScreen()
{



	if (!player_initialized && graphics::getGlobalTime() > 2000) {
		player = new Player(*this);
		player_initialized = true;
		player->Setlife(1.0f);
		meteorite = new Enemy(*this);
		ufo = new Enemy(*this);

	}

	if (player && player->getRemainingLife() == 0) {

		if (scores[0] < num + 10) {
			scores[0] = num + 10;
			Quicksort(scores, 0, 9);

		}
		xp += num + 10;
		money += xp;
		status = STATUS_START;
		player_initialized = false;
		num = -10;
	}


	if (player)
		player->update();

	if (laser) {
		if (time1 == 2) {
			time1 = 0;
			laser->active = false;
			laser = nullptr;
			delete laser;
		}
		else { time1++; }
	}
	spawnMeteorite();
	checkLaser();
	checkMeteorite();
	spawnUfo();
	checkUfo();
	
	
	

	if (meteorite) {
		meteorite->update();
	}

	if (ufo) {
		ufo->updateUfo();
	}

	if (checkCollision()==1) {
		delete meteorite;
		meteorite = nullptr;
		
	}else if (checkCollision() == 2){
		delete ufo;
		ufo = nullptr;
	}
	if (checkExplosion()==1) {
		graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.5f, false);
		delete meteorite;
		meteorite = nullptr;
		delete laser;
		laser = nullptr;

	}
	else if (checkExplosion() == 2) {
		graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.5f, false);
		delete ufo;
		ufo = nullptr;
		delete laser;
		laser = nullptr;
	}

}
//UI MENU pou vlepei o xristis me tin eisodo tou  

void Game::drawtStartScreen()
{	
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "space-start.png";
	br.outline_opacity = 0.0f;

	//draw backgroung
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);


	char info[40];
	sprintf_s(info, "PLAY");
	graphics::drawText(100, 150, 30, info, br);

	char info2[40];
	sprintf_s(info2, "HIGHSCORES");
	graphics::drawText(100, 225, 30, info2, br);

	char info3[40];
	sprintf_s(info3, "HELP");
	graphics::drawText(100, 290, 30, info3, br);

	char info4[40];
	sprintf_s(info4, "SHOP");
	graphics::drawText(100, 365, 30, info4, br);

	char info5[40];
	sprintf_s(info5, "EXIT");
	graphics::drawText(100, 440, 30, info5, br);


	std::string str = "LEVEL.";
	str += std::to_string(xp / 200);
	graphics::drawText(820, 30, 45, str, br);

	std::string str2 = "MONEY:";
	str2 += std::to_string(money);
	str2 += "$";
	graphics::drawText(550, 30, 45, str2, br);

	

}


//background parathirou pou ekselissetai to game kai grafiki dimiourgia tou diastimoploiou,twn exthrwn kai tou laser. akoma edw ginetai i diaxeirisi tis zwis.

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "space.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	if (player)
		drawp();

	if (meteorite)
		meteorite->draw();

	if (laser )
		fireLaser();

	if (ufo)
		ufo->drawufo();


	if (player) {
		char info[40];
		sprintf_s(info, "(Score: %d)", num);
		graphics::drawText(50, 50, 40, info, br);
	}
 

	float player_life = player ? player->getRemainingLife() : 0.0f;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);


}
//UI gia tin epilogi Help apo to menu. 

void Game::updateHelpScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed && ms.cur_pos_x > 840 && ms.cur_pos_x < 1100 && ms.cur_pos_y>0 && ms.cur_pos_y < 220) {
		graphics::playSound(std::string(ASSET_PATH) + "button.mp3", 0.5f, false);


		status = STATUS_START;

	}
}

//UI tou parathyrou tis Help pou mas pliroforei pws paizetai to paixnidi.

void Game::drawHelpScreen()
{
	graphics::Brush br;

	char info[40];
	sprintf_s(info, "BACK");
	graphics::drawText(850, 50, 30, info, br);

	char info1[40];
	sprintf_s(info1, "BUTTONS:");
	graphics::drawText(100, 50, 35, info1, br);

	char info2[60];
	sprintf_s(info2, "Press W to go to the top of the screen.");
	graphics::drawText(110, 90, 30, info2, br);

	char info3[60];
	sprintf_s(info3, "Press S to go to the bottom of the screen.");
	graphics::drawText(110, 130, 30, info3, br);

	char info4[60];
	sprintf_s(info4, "Press A to go to the left of the screen.");
	graphics::drawText(110, 170, 30, info4, br);
	char info5[60];
	sprintf_s(info5, "Press D to go to the right of the screen.");
	graphics::drawText(110, 210, 30, info5, br);
	char info6[60];
	sprintf_s(info6, "Press Q to shoot.");
	graphics::drawText(110, 250, 30, info6, br);
}

//analoga me to status kanei update to analogo screen
void Game::update() {

	
	if (status == STATUS_START) {
		updateStartScreen();
	} 
	else if(status == STATUS_PLAYING) {
		updateLevelScreen();
	}
	else if (status == STATUS_SCORE) {
		updateScoreScreen();
	}
	else if (status==STATUS_EXIT){ exit(0); 
	}
	else if (status == STATUS_HELP) {
		updateHelpScreen();
	}
	else if (status == STATUS_SHOP) {
		updateShopScreen();
	}
}

	
//analoga me to status kanei draw to analogo screen
void Game::draw()
{
	if (status == STATUS_START) {
		drawtStartScreen();
	}
	else if(status==STATUS_PLAYING){
		drawLevelScreen();

	}
	else if (status == STATUS_SCORE) {
		drawScoreScreen();
	}
	else if (status == STATUS_HELP) {
	    drawHelpScreen();
	}
	else if (status == STATUS_SHOP) {
		drawShopScreen();
	}
	

}
//arxikopoihsh mousikhs kai font
void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "let.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "mus1.mp3",0.5f,true,3000);
}
//metatropi diastasewn window se canva.

float Game::window2canvasX(float x)
{
	return x*CANVAS_WIDTH/(float)window_width;
}

float Game::window2canvasY(float y)
{
	return y* CANVAS_HEIGHT / (float)window_height;
}



//Constructor
Game::Game()
{
}

//Destructor
Game::~Game()
{
	if (player) {
		delete player;
	}
}
