/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#ifndef SPELLIST_H
#define SPELLIST_H

#include <map>
#include <string>
#include <memory>
#include "game.h"

using namespace std;


class RandomDmg3 :public Spell
{
public:
	void operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game);
};





#endif

