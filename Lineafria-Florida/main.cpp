#include "Game.h"
#include <memory>

/************************************
* @method:   main
* @access:   public
* @return    int
* @brief:    Método principal del programa. Se encarga de la ejecución del juego mientras la ventana siga abierta.
* @details:  Sin comentarios.
*************************************/
int main() {
	std::unique_ptr<Game> gameLoop(new Game);
	while (!gameLoop.get()->GetWindow().lock()->IsDone()) {
		gameLoop->HandleInput();
		gameLoop->Update();
		gameLoop->Render();
	}
}