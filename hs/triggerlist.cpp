/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#include "game.h"



void TriggerFilter::setFunc(shared_ptr<Spell> f)
{
	this->func = f;
}

void TriggerFilter::detectGameEvent(shared_ptr<GameEvent> event)
{
	bool satisfy = true;
	auto scDetect = event->getSource();
	if (this->source!=nullptr)
	{
		satisfy = satisfy&(scDetect->isBelongTo(this->source));
		if (!satisfy)
		{
			cout << event->getType() << " not satisfy" << endl;
			return;
		}
	}
	auto tarDetect = event->getTarget();
	if (this->target!=nullptr)
	{
		satisfy = satisfy&(tarDetect->isBelongTo(this->target));
		if (!satisfy)
		{
			cout << event->getType() << " not satisfy" << endl;
			return;
		}
	}

	assert(satisfy == true);

	(*func)(event->getSourceObj(), event->getTargetObj(), event->getGame());

}



void TriggerEventlist::add(const string& s, shared_ptr<TriggerFilter> p)
{
	this->_map.insert(pair<string, shared_ptr<TriggerFilter> >(s, p));
}

void TriggerEventlist::dectEvent(shared_ptr<GameEvent> event)
{
	auto ret = _map.equal_range(event->getType());
	if (ret.first==ret.second)
	{
		return;
	}
	for (auto iter = ret.first; iter != ret.second;++iter)
	{
		(*(iter->second)).detectGameEvent(event);
	}
}



void Triggerlist::addTrigger(const string& name, shared_ptr<Spell> sp)
{
	this->_map[name] = sp;
}


void Triggerlist::addBuilder(const string&name, shared_ptr<Triggerbuilder> build)
{
	this->builders[name] = build;
}

shared_ptr<Spell> Triggerlist::getTrigger(const string &name)
{
	auto re = _map.find(name);
	if (re != _map.end())
	{
		return re->second;
	}
	else
		return shared_ptr<Spell>(nullptr);
}

shared_ptr<Triggerbuilder> Triggerlist::getBuilder(const string& name)
{
	auto re = builders.find(name);
	if (re != builders.end())
	{
		return re->second;
	}
	else
		return shared_ptr<Triggerbuilder>(nullptr);
}

void TriggerDmgGetCard::operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game)
{
	shared_ptr<Player> player = target->getOwner();
	
}


class TriggerDmgGetCard :public Spell
{
public:
	void operator()(shared_ptr<StageObject> source, shared_ptr<StageObject> target, Game &game)
	{
		target->getOwner();
	}
};

shared_ptr<TriggerFilter> TriggerBuilderDmgGetCard::operator()(
	shared_ptr<StageObject> source,
	shared_ptr<StageObject> target,
	Game &game)
{
	shared_ptr<TriggerFilter> filter(new TriggerFilter());
	filter->setType("getdmg");
	filter->setSource(source->getSingleRange());
	filter->setTarget(nullptr);
	auto triggerlist = Triggerlist::instance();
	auto func = triggerlist["dmggetcard"]->newInstance();
	filter->setFunc(func);
	return filter;
}