#include "Game.h"
#include <memory>

int main() {
	std::unique_ptr<Game> gameLoop(new Game);
	while (!gameLoop.get()->GetWindow().lock()->IsDone()) {
		gameLoop->HandleInput();
		gameLoop->Update();
		gameLoop->Render();
	}
}