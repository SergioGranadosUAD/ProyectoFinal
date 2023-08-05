#pragma once

class PauseMenu {
public:
	PauseMenu();

	void HandleInput();
	void Update();
	void Render();

	inline bool GameResumed() { return mIsGameResumed; }
private:
	bool mIsGameResumed;
};
