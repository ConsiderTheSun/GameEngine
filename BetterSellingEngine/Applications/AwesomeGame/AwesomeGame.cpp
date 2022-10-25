

#include "AwesomeGame.h"

void AwesomeGame::Setup() {
	bse = BetterSellingEngine::GetInstance();
}

void AwesomeGame::Start() {
	bse->Start();
	delete(bse);
}

