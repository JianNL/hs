/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/

#include "game.h"



void Game::initTimer()
{
	std::thread thrd(&Game::timerProc, this);
	this->thrdTimer = std::move(thrd);
}

void Game::timerProc()
{
	while (1)
	{
		this_thread::sleep_for(std::chrono::seconds(1));
		cout << timeCount++ << endl;
	}

}


shared_ptr<Player> Game::getOppositePlayer(shared_ptr<Player> player)
{
	if (this->players.size()!=2)
	{
		cerr << "error player's numer" << endl;
		return nullptr;
	}
	if (player->getID()==this->players[0]->getID())
	{
		return this->players[0];
	}
	else
	{
		return this->players[1];
	}
}


shared_ptr<Player> Game::getOppositePlayerByID(int id)
{
	if (this->players.size()!=2)
	{
		cerr << "error player's numer" << endl;
		return nullptr;
	}
	if (this->players[0]->getID()==id)
	{
		return players[1];
	}
	else
	{
		return players[0];
	}
}

shared_ptr<Player> Game::getPlayerByID(int id)
{
	if (this->players.size()!=2)
	{
		cerr << "error player's numer" << endl;
		return nullptr;
	}
	for (auto &e:this->players)
	{
		if (e->getID()==id)
		{
			return e;
		}
	}
	return nullptr;
}


void Game::testTimer()
{
	initTimer();
}

shared_ptr<GameEvent> GameEvent::buildGameEvent(
	const string& type,
	shared_ptr<Range> sc,
	shared_ptr<Range> tar,
	shared_ptr<StageObject> scObj,
	shared_ptr<StageObject> tarObj)
{
	shared_ptr<GameEvent> event(new GameEvent());
	event->setType(type);
	event->setSource(sc);
	event->setTarget(tar);
	event->setSourceObj(scObj);
	event->setTargetObj(tarObj);
	event->setGame(scObj->getGame());
	return event;

}