#pragma once

#include <memory>
#include <cugl/cugl.h>
#include "Enemy.h"
#include <vector>
#include "ally.h"

class Board {
private:

public:
	std::shared_ptr<cugl::Texture> blankTexture;

	int height;
	int width;

	std::unordered_map<int, std::unordered_map<int, int>> tiles;

	Board() : height(5), width(5) {
		configure_size(5, 5);
	}
	Board(int h, int w) : height(h), width(w) {
		configure_size(w, h);
	}
	~Board() {}

	void configure_size(int width, int height);

	void configureToColor(float x2, float y2, int newColor);
	void configureToColor(cugl::Vec2 loc , int newColor);

	cugl::Vec2 getXY(float x2, float y2);
	cugl::Vec2 getXY(cugl::Vec2 loc);

	void draw(const std::shared_ptr<cugl::SpriteBatch>& batch);
	void drawAlly(const std::shared_ptr<cugl::SpriteBatch>& batch, std::shared_ptr<Ally> ally);
	cugl::Rect getBoundsOfGrid(int x, int y);
};