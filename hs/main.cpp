/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/

#include <iostream>
#include "game.h"
#include "test.h"
#include "common.h"


using namespace std;

void global_init()
{
	Spellist& list = Spellist::instance();
	list.add("random damage 3", shared_ptr<Spell>(new RandomDmg3()));
}


int main()
{
	cout << "test of hs" << endl;

	{
		//test of Game Timer
		Game game;
		game.testTimer();
		global_init();
		test(game);
		while (1)
		{
		}

	}

	cout << "pleas input any key to exit" << endl;
	int i;
	cin >> i;
}
