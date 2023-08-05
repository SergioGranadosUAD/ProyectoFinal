#include "Game.h"
#include "Application.h"
#include <memory>

/************************************
* @method:   main
* @access:   public
* @return    int
* @brief:    M�todo principal del programa. Se encarga de la ejecuci�n del juego mientras la ventana siga abierta.
* @details:  Sin comentarios.
*************************************/
int main() {
	std::unique_ptr<Application> gameApp(new Application);
	std::shared_ptr<Window> window = gameApp->GetWindow().lock();
	while (!window->IsDone()) {
		gameApp->HandleInput();
		gameApp->Update();
		gameApp->Render();
	}
}