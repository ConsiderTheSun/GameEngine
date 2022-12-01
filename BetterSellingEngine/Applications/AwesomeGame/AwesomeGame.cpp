#include "AwesomeGame.h"

void AwesomeGame::Setup() {
	srand(static_cast <unsigned> (time(0)));


	bse = BetterSellingEngine::GetInstance();
	bse->Initialize("This is a game");

	CreateWindow();

	bse->SetInitialScene(new MainMenuScene());
}

void AwesomeGame::CreateWindow() {
	GameWindow* awesomeWindow = bse->GetWindow();

	awesomeWindow->SetAspectRatio(1, 1);
	awesomeWindow->SetMinWindowWidth(1000);
}

void AwesomeGame::Start() {

	bse->Start();
	delete(bse);
}

