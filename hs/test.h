/* ==============================
* Author: yj
* Time：$time$
* FileName：$safeitemname$
* ===============================
*/
#include <fstream>
#include <string>
#include <iostream>
#include "json/json.h"
#include "game.h"


#pragma comment(lib,"lib_json.lib")

using namespace std;

void test(Game &game)
{
	fstream file("card.json", ios::in);
	string jsonline;
	getline(file, jsonline);
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(jsonline,root))
	{
		cout << "parse error" << endl;
		return;
	}
	
	shared_ptr<AccompanyCard> card(new AccompanyCard());
	card->initWithJson(jsonline);
	auto a = AccompanyCard::buildAccompany(card,game,1);
	

}
