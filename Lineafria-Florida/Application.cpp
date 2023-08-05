#include "Application.h"

Application::Application():
	mWindow(std::make_shared<Window>("Lineafria Florida", sf::Vector2u(1360, 768))), mElapsed(std::make_shared<float>(0)), mState(GAME_STATE::MENU), mGame(nullptr) {
	mRenderWindow = mWindow->GetMWindow();
	mMainMenu = std::make_unique<MainMenu>(mWindow, mRenderWindow);
}

void Application::HandleInput() {
	switch (mState) {
	case GAME_STATE::MENU:
		mMainMenu->HandleInput();
		break;
	case GAME_STATE::PLAYING:
		mGame->HandleInput();
	}
}

void Application::Update() {
	switch (mState) {
	case GAME_STATE::MENU:
		mMainMenu->Update();
		if(mMainMenu->GameStarted()){
			mGame = std::make_unique<Game>(mWindow, mElapsed);
			mState = GAME_STATE::PLAYING;
			mMainMenu.reset(nullptr);
		}
		break;
	case GAME_STATE::PLAYING:
		mGame->Update();
	}
}
void Application::Render() {
	switch(mState){
	case GAME_STATE::MENU:
		mMainMenu->Render();
		break;
	case GAME_STATE::PLAYING:
		mGame->Render();
		break;
	}
}

/************************************
* @method:   GetElapsed
* @access:   public
* @return    weak_ptr<float>
* @brief:    Este m�todo devuelve el tiempo transcurrido desde el �ltimo reinicio del reloj.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<float> Application::GetElapsed() {
	return mElapsed;
}

/************************************
* @method:   GetWindow
* @access:   public
* @return    weak_ptr<Window>
* @brief:    Este m�todo devuelve un puntero a la ventana para que pueda ser ocupada.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<Window> Application::GetWindow() {
	std::weak_ptr<Window> windowPtr = mWindow;
	return windowPtr;
}

void Application::RestartClock() {
	*mElapsed = mClock.restart().asSeconds();
}