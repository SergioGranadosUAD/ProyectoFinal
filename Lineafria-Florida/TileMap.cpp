#include "TileMap.h"

bool TileMap::Load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height) {
	if (!mTileset.loadFromFile("Resources/" + tileset)) {
		return false;
	}

	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j) {
			int tileNumber = tiles[i + j * width];
			std::cout << "TileNumber: " << tileNumber << std::endl;

			sf::Vector2i texturePos = GetTexturePosition(tileNumber);

			sf::Vertex* quad = &mVertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(texturePos.x, texturePos.y);
			quad[1].texCoords = sf::Vector2f(texturePos.x + tileSize.x, texturePos.y);
			quad[2].texCoords = sf::Vector2f(texturePos.x + tileSize.x, texturePos.y + tileSize.y);
			quad[3].texCoords = sf::Vector2f(texturePos.x, texturePos.y + tileSize.y);
		}
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &mTileset;
	target.draw(mVertices, states);
}

sf::Vector2i TileMap::GetTexturePosition(int tileNumber) {
	sf::Vector2i texturePos;
	switch (tileNumber) {
		//Void
	case -1:
		texturePos.x = 160;
		texturePos.y = 64;
		break;
		//Grass (NW, NE, SW, SE)
	case 1:
		texturePos.x = 0;
		texturePos.y = 0;
		break;
	case 2:
		texturePos.x = 32;
		texturePos.y = 0;
		break;
	case 3:
		texturePos.x = 0;
		texturePos.y = 32;
		break;
	case 4:
		texturePos.x = 32;
		texturePos.y = 32;
		break;
		//Brown floor (NW, NE, SW, SE)
	case 5:
		texturePos.x = 64;
		texturePos.y = 0;
		break;
	case 6:
		texturePos.x = 96;
		texturePos.y = 0;
		break;
	case 7:
		texturePos.x = 64;
		texturePos.y = 32;
		break;
	case 8:
		texturePos.x = 96;
		texturePos.y = 32;
		break;
		//Gray floor (NW, NE, SW, SE)
	case 9:
		texturePos.x = 128;
		texturePos.y = 0;
		break;
	case 10:
		texturePos.x = 160;
		texturePos.y = 0;
		break;
	case 11:
		texturePos.x = 128;
		texturePos.y = 32;
		break;
	case 12:
		texturePos.x = 160;
		texturePos.y = 32;
		break;
		//Red wall corners (NW, NE, SW, SE) rotations
	case 13:
		texturePos.x = 0;
		texturePos.y = 256;
		break;
	case 14:
		texturePos.x = 32;
		texturePos.y = 256;
		break;
	case 15:
		texturePos.x = 0;
		texturePos.y = 288;
		break;
	case 16:
		texturePos.x = 32;
		texturePos.y = 288;
		break;
		//Gray wall corners (NW, NE, SW, SE) rotations
	case 17:
		texturePos.x = 64;
		texturePos.y = 256;
		break;
	case 18:
		texturePos.x = 96;
		texturePos.y = 256;
		break;
	case 19:
		texturePos.x = 64;
		texturePos.y = 352;
		break;
	case 20:
		texturePos.x = 96;
		texturePos.y = 352;
		break;
		//Red wall (W, E, N, S) rotations
	case 21:
		texturePos.x = 0;
		texturePos.y = 320;
		break;
	case 22:
		texturePos.x = 32;
		texturePos.y = 320;
		break;
	case 23:
		texturePos.x = 0;
		texturePos.y = 352;
		break;
	case 24:
		texturePos.x = 32;
		texturePos.y = 352;
		break;
		//Gray wall (W, E, N, S) rotations
	case 25:
		texturePos.x = 64;
		texturePos.y = 320;
		break;
	case 26:
		texturePos.x = 96;
		texturePos.y = 320;
		break;
	case 27:
		texturePos.x = 64;
		texturePos.y = 352;
		break;
	case 28:
		texturePos.x = 96;
		texturePos.y = 352;
		break;
		//Thick red wall corners (NW, NE, SW, SE) rotations
	case 29:
		texturePos.x = 128;
		texturePos.y = 128;
		break;
	case 30:
		texturePos.x = 160;
		texturePos.y = 128;
		break;
	case 31:
		texturePos.x = 128;
		texturePos.y = 160;
		break;
	case 32:
		texturePos.x = 160;
		texturePos.y = 160;
		break;
		//Thick gray wall corners (NW, NE, SW, SE) rotations
	case 33:
		texturePos.x = 128;
		texturePos.y = 256;
		break;
	case 34:
		texturePos.x = 160;
		texturePos.y = 256;
		break;
	case 35:
		texturePos.x = 128;
		texturePos.y = 288;
		break;
	case 36:
		texturePos.x = 160;
		texturePos.y = 288;
		break;
		//Thick red wall (W, E, N, S) rotations
	case 37:
		texturePos.x = 128;
		texturePos.y = 224;
		break;
	case 38:
		texturePos.x = 160;
		texturePos.y = 224;
		break;
	case 39:
		texturePos.x = 128;
		texturePos.y = 192;
		break;
	case 40:
		texturePos.x = 160;
		texturePos.y = 192;
		break;
		//Thick gray wall (W, E, N, S) rotations
	case 41:
		texturePos.x = 128;
		texturePos.y = 352;
		break;
	case 42:
		texturePos.x = 160;
		texturePos.y = 352;
		break;
	case 43:
		texturePos.x = 128;
		texturePos.y = 320;
		break;
	case 44:
		texturePos.x = 160;
		texturePos.y = 320;
		break;
		//Thick red wall filler
	case 45:
		texturePos.x = 144;
		texturePos.y = 144;
		break;
		//Thick gray wall filler
	case 46:
		texturePos.x = 144;
		texturePos.y = 272;
		break;
		//Red wall corner (SE, SW, NE, NW)
	case 47:
		texturePos.x = 0;
		texturePos.y = 384;
		break;
	case 48:
		texturePos.x = 32;
		texturePos.y = 384;
		break;
	case 49:
		texturePos.x = 0;
		texturePos.y = 416;
		break;
	case 50:
		texturePos.x = 32;
		texturePos.y = 416;
		break;
		//Gray wall corner (SE, SW, NE, NW)
	case 51:
		texturePos.x = 64;
		texturePos.y = 384;
		break;
	case 52:
		texturePos.x = 96;
		texturePos.y = 384;
		break;
	case 53:
		texturePos.x = 64;
		texturePos.y = 416;
		break;
	case 54:
		texturePos.x = 96;
		texturePos.y = 416;
		break;
	}
	return texturePos;
}