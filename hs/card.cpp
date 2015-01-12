/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#include "game.h"


void Card::initWithJson(const string& json)
{
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(json, root))
	{
		cout << "reader parse error" << endl;
		return;
	}
	this->type = root["type"].asString();
	this->cost = root["cost"].asInt();
	this->ap = root["ap"].asInt();
	this->hp = root["hp"].asInt();
	this->spell = root["spell"].asString();
	this->aura = root["aura"].asString();
	this->trigger = root["trigger"].asString();
	this->name = root["name"].asString();

}


shared_ptr<Accompany> AccompanyCard::buildAccompany(shared_ptr<AccompanyCard> card,Game& game,int pos)
{
	shared_ptr<Accompany> acc = make_shared<Accompany>(card, game);
	return acc;
}



