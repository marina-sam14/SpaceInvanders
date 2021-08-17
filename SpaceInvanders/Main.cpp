#include "../sgg/include/graphics.h"
#include "Game.h"
#include "config.h"


//window dimensions

void resize(int w,int h) {
    Game* game = reinterpret_cast <Game*> (graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);

}
//cast tou pointer se Game 

void update(float ms)
{
    Game* game = reinterpret_cast <Game *> (graphics::getUserData());
    game->update();
}
//cast tou pointer se Game 

void draw()
{
    Game* game = reinterpret_cast <Game*> (graphics::getUserData());
    game->draw();
   
}
//UI

int main()
{
    Game mygame;
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game1");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	//arxi paixnidiou

    mygame.init();
    graphics::startMessageLoop();

    return 0;
}