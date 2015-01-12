/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#ifndef REQUESTEVENT_H
#define REQUESTEVENT_H

#include <iostream>
#include <string>
#include <thread>
#include "game.h"

using namespace std;



class RequestEventParser
{
public:
	RequestEventParser(Game &game) :ggame(game)
	{

	}
	void start();
private:
	Game &ggame;

};


#endif