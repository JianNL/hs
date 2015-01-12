/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#include "spellist.h"

Spellist Spellist::spellist = Spellist();

void RandomDmg3::operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game)
{
	int count = 3;
	shared_ptr<Player> owner = source->getOwner();
	//获取敌对
	shared_ptr<Player> ops = game.getOppositePlayer(owner);
	auto& all = ops->getAllAccompanys();
	while (count>0)
	{
	}
}


shared_ptr<Spell>& Spellist::operator [](const string& name)
{
	auto re = _map.find(name);
	if (re != _map.end())
	{
		return re->second;
	}
	else
		return shared_ptr<Spell>(nullptr);
}

const shared_ptr<Spell>& Spellist::operator [](const string& name) const
{
	auto re = _map.find(name);
	if (re != _map.end())
	{
		return re->second;
	}
	else
		return nullptr;
}


void Spellist::add(const string& name, shared_ptr<Spell> sp)
{
	this->_map[name] = sp;
}
