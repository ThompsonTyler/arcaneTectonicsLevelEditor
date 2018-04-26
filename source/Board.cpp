#include "Board.h"
#include "cugl\cugl.h"

using namespace cugl;

const int x_start = 120;
const int x_end = 520;
const int y_start = 255;
const int y_end = 655;

int tw = x_end - x_start;
int th = y_end - y_start;


void Board::configure_size(int width, int height) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (tiles.count(x) > 0) { //Has x value
				std::unordered_map<int, int> vals = tiles.at(x);
				if (vals.count(y) == 0) { //Does not have value, add values up to height
					for (int i = y; i < height; i++) {
						vals[i] = -1;
					}
					tiles[x] = vals;
				}
			}
			else {
				for (int i = x; i < width; i++) {
					std::unordered_map<int, int> temp;
					for (int j = 0; j < height; j++) {
						temp[j] =-1;
					}

					tiles[x] = temp;
				}
			}
		}
	}

	this->width = width;
	this->height = height;
}


void Board::configureToColor(float x2, float y2, int newColor) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			//CULog("DRAW %d, %d", x, y);
			Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
			if (bounds.contains(Vec2(x2, y2))) {
				tiles[x][y] = newColor;
			}
		}
	}
}

cugl::Vec2 Board::getXY(float x2, float y2) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			//CULog("DRAW %d, %d", x, y);
			Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
			if (bounds.contains(Vec2(x2, y2))) {
				return Vec2(x, y);
			}
		}
	}
	return Vec2(-1, -1);
}

cugl::Vec2 Board::getXY(Vec2 loc) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			//CULog("DRAW %d, %d", x, y);
			Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
			if (bounds.contains(Vec2(loc.x, loc.y))) {
				return Vec2(x, y);
			}
		}
	}
	return Vec2(-1, -1);
}

void Board::configureToColor(Vec2 loc, int newColor) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			//CULog("DRAW %d, %d", x, y);
			Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
			if (bounds.contains(Vec2(loc.x, loc.y))) {
				tiles[x][y] = newColor;
			}
		}
	}
}

void Board::draw(const std::shared_ptr<cugl::SpriteBatch>& batch) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;

	batch->begin();

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			//CULog("DRAW %d, %d", x, y);
			Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
			Color4 drawColor = Color4(196, 196, 196, 255);
			switch (tiles[x][y]) {
				case 0:
					drawColor = Color4(255, 82, 188, 255);
					break;
				case 1:
					drawColor = Color4(29, 134, 223, 255);
					break;
				case 2:
					drawColor = Color4(22, 255, 236, 255);
					break;
				case 3:
					drawColor = Color4(255, 66, 22, 255);
					break;
				case 4:
					drawColor = Color4(5, 181, 1, 255);
					break;
				case 5:
					drawColor = Color4(136, 1, 181, 255);
					break;
				default:
					break;
			}
			batch->draw(blankTexture, drawColor , bounds);
		}
	}

	batch->end();
}

void Board::drawAlly(const std::shared_ptr<cugl::SpriteBatch>& batch, std::shared_ptr<Ally> ally) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;

	batch->begin();

	Rect bounds(x_start + ally->x*indWidth + 5 * (ally->x - 1) + indWidth / 5, y_start + ally->y*indHeight + 5 * (ally->y - 1) + indHeight / 5, indWidth - 2*indWidth/5, indHeight - 2 * indHeight / 5);
	batch->draw(blankTexture, ally->isMika ? Color4::WHITE : Color4::BLACK, bounds);

	batch->end();
}

cugl::Rect Board::getBoundsOfGrid(int x, int y) {
	float indWidth = ((tw + 5) / width) - 5;
	float indHeight = ((th + 5) / height) - 5;
	
	Rect bounds(x_start + x*indWidth + 5 * (x - 1), y_start + y*indHeight + 5 * (y - 1), indWidth, indHeight);
	return bounds;
}