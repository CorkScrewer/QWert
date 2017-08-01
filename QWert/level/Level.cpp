#include "Level.h"
#include "../entities/Player.h"

Level::Level(const char* filePath) {
	std::ifstream file;
	file.open(filePath);
	if (file.fail()) {
		Errors::FATAL("Failed to load " + std::string(filePath) + " Into the game!");
	}

	std::string tmp;

	while (std::getline(file, tmp)) {
		levelData.push_back(tmp);
	}

	for (int y = 0; y < levelData.size(); y++) {
		for (int x = 0; x < levelData[y].size(); x++) {
			char currentChar = levelData[y][x];

			switch (currentChar) {
			case '@': {
				Player* player = new Player(this, Rect(x * DEFAULT_TILE_SIZE, y * DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE));
				entities.insert(entities.begin(), player);
				break; 
			}
			case '#': {
				Ground* tile = new Ground(Rect(x * DEFAULT_TILE_SIZE, y * DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE));
				tiles.push_back(tile);
				entities.push_back(tile);
				break;
			}
			}
		}
	}
}

Level::~Level() {
	for (unsigned int i = 0; i < tiles.size(); i++) {
		delete tiles[i];
	}
}

void Level::init(SDL_Renderer* renderer) {
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->init(renderer);
	}
}

void Level::update(Input& input, float dt) {
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->update(input, dt);
	}
}

void Level::render(SDL_Renderer* renderer) {
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities[i]->isOnScreen()) {
			entities[i]->render(renderer);
		}
	}
}