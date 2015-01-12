/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#include "game.h"


shared_ptr<Accompany> Player::getAccompanyByID(int id)
{
	if (this->accompanys.size()==0)
	{
		return nullptr;
	}
	for (auto &e:this->accompanys)
	{
		if (e->getID()==id)
		{
			return e;
		}
	}
	return nullptr;
}

shared_ptr<StageObject> Player::getObjByID(int id)
{
	for (auto &e:this->accompanys)
	{
		if (e->getID()==id)
		{
			return e;
		}
	}
	if (this->weapon)
	{
		if (this->weapon->getID()==id)
		{
			return this->weapon;
		}
	}
	return nullptr;
}

list<shared_ptr<Accompany> >& Player::getAllAccompanys()
{
	return this->accompanys;
}

void Player::addAccompanyToPos(shared_ptr<Accompany> accompany, int pos)
{
	int count = 0;
	if (pos > this->accompanys.size())
	{
		cerr << "no pos" << endl;
		return;
	}
	auto iter = this->accompanys.begin();
	while (iter!=accompanys.end())
	{
		if ((count++)==pos-1)
		{
			this->accompanys.insert(iter, accompany);
			auto trie = TriggerEventlist::instance();
			auto event = GameEvent::buildGameEvent(
				"usecard",
				accompany->getSingleRange(),
				nullptr,
				accompany,
				nullptr);
			trie.dectEvent(event);
			return;
		}
		iter++;
	}
	
}



void Player::useCardWithoutTarget(shared_ptr<Card> card, int pos = 0)
{
	//if use the acc card
	if (card->getCardType()==Card::ACCOMPANYCARD)
	{
		auto acc = AccompanyCard::buildAccompany(dynamic_pointer_cast<AccompanyCard>(card), game, pos);
		this->addAccompanyToPos(acc, pos);
		auto lst = Triggerlist::instance();
		auto builder = lst.getBuilder(card->getTrigger());
		shared_ptr<TriggerFilter> filter = (*builder)(acc, nullptr, game);
		auto eventlist = TriggerEventlist::instance();
		eventlist.add(card->getTriggerType(), filter);
		auto trie= TriggerEventlist::instance();
		trie.dectEvent(GameEvent::buildGameEvent(
			"summonacc",
			acc->getSingleRange(),
			nullptr,
			acc,
			nullptr
			));
	}
	
}
