#include "Application.h"

Application::Application():
	mWindow(std::make_shared<Window>("Curvafria Florida", sf::Vector2u(1360, 768))), mElapsed(std::make_shared<float>(0)), mState(GAME_STATE::MENU), mGame(nullptr) {
	mRenderWindow = mWindow->GetMWindow();
	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
		windowPtr->setVerticalSyncEnabled(true);
		windowPtr->setKeyRepeatEnabled(false);
		windowPtr->setMouseCursorVisible(false);
	}
	mMainMenu = std::make_unique<MainMenu>(mWindow, mRenderWindow);
}

Application::~Application() {

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
			mGame = std::make_unique<Game>(mWindow, mElapsed, "Level1");
			mState = GAME_STATE::PLAYING;
			mMainMenu.reset(nullptr);
		}
		break;
	case GAME_STATE::PLAYING:
		mGame->Update();
		if (mGame->GameFinished()) {
			mGame->ResetView();
			mMainMenu = std::make_unique<MainMenu>(mWindow, mRenderWindow);
			mState = GAME_STATE::MENU;
			mGame.reset(nullptr);
		}
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
* @brief:    Este método devuelve el tiempo transcurrido desde el último reinicio del reloj.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<float> Application::GetElapsed() {
	return mElapsed;
}

/************************************
* @method:   GetWindow
* @access:   public
* @return    weak_ptr<Window>
* @brief:    Este método devuelve un puntero a la ventana para que pueda ser ocupada.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<Window> Application::GetWindow() {
	std::weak_ptr<Window> windowPtr = mWindow;
	return windowPtr;
}

void Application::RestartClock() {
	*mElapsed = mClock.restart().asSeconds();
}