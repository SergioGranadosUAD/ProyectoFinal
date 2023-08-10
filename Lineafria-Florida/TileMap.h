#pragma once
#include "Window.h"

/************************************
* @class:    TileMap
* @access:   public
* @brief:    Esta clase se encarga de cargar el tilemap y de dibujarlo.
* @details:  El tilemap es un solo VertexArray el cual se divide entre el numero de tiles del mapa al cual se le asigna las coordenadas de texturas
*			 correspondientes a cada tile. Esto lo hace menos demandante que tener un objeto para cada tile.
*************************************/
class TileMap : public sf::Drawable, public sf::Transformable {
public:
	TileMap();
	virtual ~TileMap();
	bool Load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height);

private:
	sf::VertexArray mVertices;
	sf::Texture mTileset;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2i GetTexturePosition(int tileNumber);
};