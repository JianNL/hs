/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <memory>
#include <list>
#include <windows.h>
#include "range.h"
#include "json/json.h"
#include <assert.h>

#pragma comment(lib,"lib_json.lib")

using namespace std;

class Card;
class SpellCard;
class AccompanyCard;
class Accompany;
class Player;
class Weapon;
class Spell;
class TriggerEventlist;

class Game
{
public:
	Game() :timeCount(0)
	{

	}
	
	void initTimer();
	void timerProc();

	shared_ptr<Player> getOppositePlayer(shared_ptr<Player> player);
	shared_ptr<Player> getOppositePlayerByID(int id);
	shared_ptr<Player> getPlayerByID(int id);

	void testTimer();
private:
	int timeCount;
	std::thread thrdTimer;

	vector<shared_ptr<Player> > players;

	

};


class TriggerFilter
{
public:

	typedef shared_ptr<Spell> FuncPType;

	TriggerFilter() :type(""), source(nullptr), target(nullptr)
	{}

	void setType(const string &type)
	{
		this->type = type;
	}

	void setSource(shared_ptr<Range> source)
	{
		this->source = source;
	}

	void setTarget(shared_ptr<Range> target)
	{
		this->target = target;
	}

	const string& getType() const 
	{
		return this->type;
	}

	string& getType()
	{
		return this->type;
	}

	shared_ptr<Range> getSource()
	{
		return this->source;
	}

	shared_ptr<Range> getSource() const
	{
		return this->source;
	}

	shared_ptr<Range> getTarget()
	{
		return this->target;
	}

	shared_ptr<Range> getTarget() const
	{
		return this->target;
	}

	void setFunc(shared_ptr<Spell> f);

	void detectGameEvent(shared_ptr<GameEvent> event);

private:

	string type;
	shared_ptr<Range> source;
	shared_ptr<Range> target;

	shared_ptr<function<void(shared_ptr<StageObject>, shared_ptr<StageObject>,Game&)> > func;
};

/*
inline bool operator==(const TriggerFilter& l, const TriggerFilter& r)
{
	if (l.getType()==r.getType()&&l.getSource()==r.getSource()&&l.getTarget()==r.getTarget())
	{
		return true;
	}
	return false;
}
*/


class Triggerbuilder
{
public:

	shared_ptr<TriggerFilter> operator()(
		shared_ptr<StageObject> source,
		shared_ptr<StageObject> target,
		Game &game);

	shared_ptr<Triggerbuilder> newInstance()
	{
		return shared_ptr<Triggerbuilder>(new Triggerbuilder());
	}
	

};

class TriggerBuilderDmgGetCard :public Triggerbuilder
{
public:
	shared_ptr<TriggerFilter> operator()(
		shared_ptr<StageObject> source,
		shared_ptr<StageObject> target,
		Game &game);

	shared_ptr<Triggerbuilder> newInstance();

};

class TriggerTemplate
{
public:
	TriggerTemplate()
	{}
	virtual void operator()(shared_ptr<StageObject> source, Game &game)
	{
	}
	
};



class TriggerEventlist
{
public:
	TriggerEventlist()
	{}


	static TriggerEventlist triggerlist;
	static TriggerEventlist& instance()
	{
		return triggerlist;
	}

	void add(const string& s, shared_ptr<TriggerFilter> p);

	void dectEvent(shared_ptr<GameEvent> event);

private:

	multimap<string, shared_ptr<TriggerFilter> > _map;

	

};

class Triggerlist
{
public:

	void addTrigger(const string& name, shared_ptr<Spell> sp);

	void addBuilder(const string&name, shared_ptr<Triggerbuilder> build);

	shared_ptr<Spell> getTrigger(const string &name);

	shared_ptr<Triggerbuilder> getBuilder(const string& name);


	static Triggerlist triggerlist;

	static Triggerlist& instance()
	{
		return triggerlist;
	}
	
	
private:
	map<string, shared_ptr<Spell> > _map;
	map<string, shared_ptr<Triggerbuilder> > builders;
};


class GameEvent
{
public:

	std::string getType() const { return type; }

	void setType(std::string val) { type = val; }

	shared_ptr<Range> getSource() const { return source; }

	void setSource(shared_ptr<Range> val) { source = val; }

	shared_ptr<Range> getTarget() const { return target; }

	void setTarget(shared_ptr<Range> val) { target = val; }

	shared_ptr<StageObject> getSourceObj() const { return sourceObj; }

	void setSourceObj(shared_ptr<StageObject> val) { sourceObj = val; }

	shared_ptr<StageObject> getTargetObj() const { return targetObj; }

	void setTargetObj(shared_ptr<StageObject> val) { targetObj = val; }

	Game& getGame() const { return game; }

	void setGame(Game& val) { game = val; }

	static shared_ptr<GameEvent> buildGameEvent(const string& type,
												shared_ptr<Range> sc,
												shared_ptr<Range> tar,
												shared_ptr<StageObject> scObj,
												shared_ptr<StageObject> tarObj);


private:
	string type;

	shared_ptr<Range> source;
	shared_ptr<Range> target;

	shared_ptr<StageObject> sourceObj;
	shared_ptr<StageObject> targetObj;

	Game& game;
};


class StageObject
{
public:
	StageObject(Game& g) :game(g)
	{

	}

	void setID(int i)
	{
		this->id = i;
	}

	int getID()
	{
		return this->id;
	}

	enum Types
	{
		OBJ,
		PLAYER,
		ACCOMPANY,
		WEAPON
	};
	virtual Types getType()
	{
		return OBJ;
	}
	shared_ptr<Player> getOwner()
	{
		return owner;
	}
	void setOwner(shared_ptr<Player> player)
	{
		this->owner = player;
	}

	void setGame(Game& g)
	{
		game = g;
	}
	Game& getGame()
	{
		return game;
	}

	virtual shared_ptr<Range> getSingleRange()
	{
		auto own = this->getOwner();
		if (own->getBelongs()->getType()==Range::LPLAYER)
		{
			return shared_ptr<Range>(new LSingleRange(this->id));
		}
		if (own->getBelongs()->getType()==Range::RPLAYER)
		{
			return shared_ptr<Range>(new RSingleRange(this->id));
		}
	}

protected:
	int id;
	shared_ptr<Player> owner;
	
	Game& game;

};

class Spell
{
public:

	virtual void operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game)
	{
	}

	virtual shared_ptr<Spell> newInstance()
	{
		return shared_ptr<Spell>(new Spell());
	}

};


class Spellist
{
public:
	Spellist()
	{}
	void add(const string& name, shared_ptr<Spell> sp);
	shared_ptr<Spell>& operator[](const string &name);
	const shared_ptr<Spell>& operator[](const string &name) const;

	static Spellist spellist;

	static Spellist& instance()
	{
		return spellist;
	}


private:
	
	map<string, shared_ptr<Spell> > _map;


};


class Trigger
{
public:
	virtual void operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game)
	{
	}
};


class TriggerTemplate
{
public:
	TriggerTemplate()
	{}
	virtual void operator()(shared_ptr<StageObject> source, Game &game)
	{
	}
	
};

class Player :public StageObject
{
public:
	Player(int id, shared_ptr<Range> b,Game& g) :StageObject(g),belongs(b)
	{
		this->id = id;
	}

	shared_ptr<Accompany> getAccompanyByID(int id);
	shared_ptr<StageObject> getObjByID(int id);

	void useCardWithTarget(shared_ptr<Card> card, shared_ptr<StageObject> target, int pos=0);
	void useCardWithoutTarget(shared_ptr<Card> card,int pos=0);

	Types getType()
	{
		return PLAYER;
	}

	list<shared_ptr<Accompany> >& getAllAccompanys();
	void addAccompanyToPos(shared_ptr<Accompany> accompany, int pos);

	shared_ptr<Range> getBelongs()
	{
		return this->belongs;
	}

private:

	list<shared_ptr<Accompany> > accompanys;
	shared_ptr<Weapon> weapon;

	vector<shared_ptr<Card> > handCards;
	vector<shared_ptr<Card> > cards;

	int hp;
	int ap;

	shared_ptr<Range> belongs;

};

class Accompany :public StageObject
{
public:
	Accompany(shared_ptr<AccompanyCard> card, Game &g) :StageObject(g)
	{
		this->name = card->getName();
		this->ap = card->getAp();
		this->hp = card->getHp();
		auto splist = Spellist::instance();
		auto triglist = Triggerlist::instance();
		if (card->getSpell().length()!=0)
		{
			this->spell = splist[card->getSpell()];
		}
		if (card->getTrigger().length()!=0)
		{

			this->trigger = card->getTrigger();
			this->triggertype = card->getTriggerType();
		}
	}

	Types getType()
	{
		return ACCOMPANY;
	}

	shared_ptr<Player> getOwner();
	void setOwner(shared_ptr<Player> player);

private:

	//名字
	string name;
	//攻击力
	int ap;
	//生命值
	int hp;
	//拥有的技能
	shared_ptr<Spell> spell;
	//拥有的触发器
	string trigger;
	//拥有的触发器类型
	string triggertype;
	//拥有的增减益状态
	vector<string> buff;
	//是否可以攻击
	bool isCanAttack;

	//
	shared_ptr<Player> owner;
};


class Weapon :public StageObject
{
public:
	Weapon(Game& g) :StageObject(g)
	{

	}

	Types getType()
	{
		return WEAPON;
	}
	
private:
	int ap;
	int wear;

};

class Card
{
public:
	Card()
	{
	}

	enum CardTypes
	{
		NOTYPECARD,
		SPELLCARD,
		SECRETCARD,
		ACCOMPANYCARD,
		WEAPONCARD
	};

	virtual CardTypes getCardType()
	{
		return NOTYPECARD;
	}

	virtual void initWithJson(const string& json);


	string getType()
	{
		return this->type;
	}

	int getCost()
	{
		return this->cost;
	}

	int getAp()
	{
		return this->ap;
	}

	int getHp()
	{
		return this->hp;
	}

	int getOwnerID()
	{
		return this->ownerID;
	}

	void setOwnerID(int id)
	{
		this->ownerID = id;
	}

	string getSpell()
	{
		return this->spell;
	}

	string getAura()
	{
		return this->aura;
	}


	string getName()
	{
		return this->name;
	}

	void setCost(int para)
	{
		this->cost = para;
	}

	void setAp(int para)
	{
		this->ap = para;
	}

	void setHp(int para)
	{
		this->hp = para;
	}

	const string& getTrigger()
	{
		return this->trigger;
	}

	void setTrigger(const string& t)
	{
		this->trigger = t;
	}

	void setTriggerType(const string& t)
	{
		this->triggertype = t;
	}

	const string& getTriggerType()
	{
		return this->triggertype;
	}

protected:

	string type;
	int cost;
	int ap;
	int hp;
	int ownerID;
	string spell;
	string aura;
	string trigger;
	string triggertype;
	string effect;
	string name;
	
};

class SpellCard:public Card
{
public:


	CardTypes getCardType()
	{
		return Card::SPELLCARD;
	}


private:

};


class AccompanyCard:public Card
{
public:

	CardTypes getCardType()
	{
		return Card::ACCOMPANYCARD;
	}

	static shared_ptr<Accompany> buildAccompany(shared_ptr<AccompanyCard> card,Game &game,int pos);

private:


};




class TriggerDmgGetCard :public Spell
{
public:
	virtual void operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game);

	virtual shared_ptr<Spell> newInstance();

};


#endif
