#include "Window.h"

/************************************
* @method:   Window
* @access:   public
* @return:   void
* @brief:    Constructor default de la clase Window.
* @details:  Se construye la ventana por medio de varios métodos.
*************************************/
Window::Window() {
	Setup("Game Window", sf::Vector2u(800, 600));
}

/************************************
* @method:   Window
* @access:   public
* @return:	 void
* @brief:    Constructor con argumentos de la clase Window.
* @details:  Se construye la ventana por medio de varios métodos.
*************************************/
Window::Window(const std::string& mTitle, const sf::Vector2u& mSize) {
	Setup(mTitle, mSize);
}

/************************************
* @method:   ~Window
* @access:   public
* @return:	 void
* @brief:    Este método revisa si los proyectiles colisionan con jugador o un enemigo, y realiza los comportamientos apropiados.
* @details:  Sin detalles.
*************************************/
Window::~Window() {
	Destroy();
}

/************************************
* @method:   Setup
* @access:   private
* @return:   void
* @brief:    Parte de la construcción de la clase, establece los valores de los miembros de la clase en base a los argumentos.
* @details:  Primera parte de los métodos constructores, llama a otro para seguir construyendo la clase.
*************************************/
void Window::Setup(const std::string& mTitle, const sf::Vector2u& mSize) {
	mWindowTitle = mTitle;
	mWindowSize = mSize;
	mIsFullscreen = false;
	mIsDone = false;
	Create();
}

/************************************
* @method:   Create
* @access:   private
* @return:   void
* @brief:    Parte de la construcción de la clase, establece el estilo de la ventana y se lo asigna.
* @details:  Segunda parte de los métodos constructores.
*************************************/
void Window::Create() {
	sf::Uint32 windowStyle = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(mWindowSize.x, mWindowSize.y, 32), mWindowTitle, windowStyle);
	//mWindow.create({ mWindowSize.x, mWindowSize.y, 32 }, mWindowTitle, windowStyle);
}

/************************************
* @method:   Destroy
* @access:   private
* @return:   void
* @brief:    Método destructor, cierra la ventana al momento de que se termina de ocupar.
* @details:  Sin detalles
*************************************/
void Window::Destroy() {
	mWindow->close();
}

/************************************
* @method:   FinishWindow
* @access:   public
* @return:   void
* @brief:    Le indica a la clase que se terminó de ocupar la ventana para su cierre.
* @details:  Sin comentarios.
*************************************/
void Window::FinishWindow() {
	mIsDone = true;
}

/************************************
* @method:   ToggleFullScreen
* @access:   public
* @return:   void
* @brief:    Cambia el estado de la ventana, entre pantalla completa y ventana.
* @details:  Se destruye la ventana para poder volver a crearla con la nueva resolución.
*************************************/
void Window::ToggleFullscreen() {
	mIsFullscreen = !mIsFullscreen;
	Destroy();
	Create();
}

/************************************
* @method:   BeginDraw
* @access:   public
* @return:   void
* @brief:    Método que limpia la ventana para que se pueda volver a dibujar sobre esta.
* @details:  Sin comentarios.
*************************************/
void Window::BeginDraw() {
	mWindow->clear();
}

/************************************
* @method:   EndDraw
* @access:   public
* @return:   void
* @brief:    Método que muestra todos los elementos dibujados en la ventana.
* @details:  Sin comentarios.
*************************************/
void Window::EndDraw() {
	mWindow->display();
}

/************************************
* @method:   IsDone
* @access:   public
* @return:   bool
* @brief:    Método que devuelve el booleano que indica si la ventana se seguirá usando o si ya se ha terminado de ocupar para destruirla.
* @details:  Sin comentarios.
*************************************/
bool Window::IsDone() {
	return mIsDone;
}

/************************************
* @method:   IsFullcreen
* @access:   public
* @return:   bool
* @brief:    Método que regresa el estado de la ventana, si se encuentra en pantalla completa o no.
* @details:  Sin comentarios.
*************************************/
bool Window::IsFullscreen() {
	return mIsFullscreen;
}

/************************************
* @method:   GetWindowSize
* @access:   public
* @return:   Vector2u
* @brief:    Método que devuelve un vector con el tamaño de la ventana.
* @details:  Sin comentarios.
*************************************/
sf::Vector2u Window::GetWindowSize() {
	return mWindowSize;
}

/************************************
* @method:   Draw
* @access:   public
* @return:   void
* @brief:    Método que dibuja el elemento indicado en la ventana.
* @details:  Sin comentarios.
*************************************/
void Window::Draw(sf::Drawable& mDrawable) {
	mWindow->draw(mDrawable);
}