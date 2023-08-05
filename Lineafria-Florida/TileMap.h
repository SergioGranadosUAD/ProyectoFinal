#pragma once
#include "Window.h"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	bool Load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height);

private:
	sf::VertexArray mVertices;
	sf::Texture mTileset;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2i GetTexturePosition(int tileNumber);
};