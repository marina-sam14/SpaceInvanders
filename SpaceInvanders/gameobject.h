#pragma once
#include "util.h"


class Collidable {
public:
	virtual Disk getCollisionHull() const = 0; //virtual kathws tha epelegei kata tin ektelesi ti eidous antikeimenou tha kataskeuastei

};
class gameobject {

protected:
	const class Game & game;
public:
	gameobject(const class Game& mygame);
		//pure virtuals: tha ilopoiithoun apo tis klaseis paidia

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;

};