#include "Enemy.h"
#include <sstream>

using namespace cugl;

int heightOfCapsule = 33;
int separation = 10;

void Enemy::draw(const std::shared_ptr<cugl::SpriteBatch>& batch, std::vector<std::shared_ptr<Label>>& labels, std::vector<std::shared_ptr<Button>>& buttons, float xStart, float xEnd, float yStart, float yEnd, int yOffset) {
	batch->begin();

	int i = 0;
	int buttonCounter = 0;
	int currentTravelled = 0;
	for (auto l = labels.begin(); l != labels.end(); l++) {
		(*l)->setVisible(false);
	}

	for (auto b = buttons.begin(); b != buttons.end(); b++) {
		(*b)->setVisible(false);
		(*b)->deactivate();
	}

	for (auto c = components.begin(); c != components.end(); c++) {
		float start = (i != yOffset ? separation : 0) + currentTravelled;
		int drawHeight = heightOfCapsule;
		if (opened[(*c).first]) {
			drawHeight += (heightOfCapsule * (*c).second.mapping.size());
		}

		float selfBottomY = drawHeight + start;
		if (i >= yOffset && selfBottomY >= 0 && selfBottomY <= yEnd - yStart) {
			std::shared_ptr<Label> ownLabel = labels.at(i);
			ownLabel->setVisible(true);

			buttons[buttonCounter]->setVisible(true);
			buttons[buttonCounter]->setPositionY(yEnd - selfBottomY + drawHeight - (heightOfCapsule - 5));
			buttons[buttonCounter]->setListener([=](const std::string& name, bool down) {
				if (down) {
					opened[(*c).first] = !opened[(*c).first];
					needRedraw = true;
				}
			});
			buttons[buttonCounter]->activate(1000 + buttonCounter);

			auto comp = (*c).second;
			ownLabel->setText(comp.getName(), true);
			ownLabel->setPositionY(yEnd - selfBottomY + drawHeight - (heightOfCapsule - 5));
			Rect bounds(xStart, yEnd - selfBottomY, xEnd - xStart, drawHeight + (start >= 0 ? 0 : start));
			batch->draw(nullptr, Color4(196, 196, 196, 255), bounds);

			currentTravelled += (drawHeight + (i != yOffset ? separation : 0));
			buttonCounter++;
		}

		if (currentTravelled >= (yEnd - yStart) - separation) {
			break;
		}
		i++;
	}
	
	for (auto l = labels.begin(); l != labels.end(); l++) {
		if ((*l)->isVisible()) {
			(*l)->draw(batch, (*l)->getNodeToWorldTransform(), Color4::WHITE);
		}
	}




	batch->end();
}

void Enemy::setupLabelFields(std::vector<std::shared_ptr<Label>>& labels, std::vector<std::shared_ptr<TextField>>& fields, float xStart, float xEnd, float yStart, float yEnd, int yOffset) {
	int i = 0;
	int currentTravelled = 0;
	for (auto l = labels.begin(); l != labels.end(); l++) {
		(*l)->setVisible(false);
	}
	for (auto l = fields.begin(); l != fields.end(); l++) {
		(*l)->deactivate();
		(*l)->setVisible(false);
	}

	for (auto c = components.begin(); c != components.end(); c++) {
		float start = (i != yOffset ? separation : 0) + currentTravelled;
		int drawHeight = heightOfCapsule;
		if (opened[(*c).first]) {
			drawHeight += (heightOfCapsule * (*c).second.mapping.size());
		}

		float selfBottomY = drawHeight + start;
		if (i >= yOffset && selfBottomY >= 0 && selfBottomY <= yEnd - yStart) {
			if (opened[(*c).first]) {
				auto comp = (*c).second;
				int individuali = 1;
				for (auto& c2 : comp.mapping) {
					std::shared_ptr<Label> ownLabel = labels.at(i);
					std::shared_ptr<TextField> ownField = fields.at(i);
					ownLabel->setVisible(true);
					ownField->setVisible(true);
					ownLabel->setPositionY(yEnd - selfBottomY + drawHeight - heightOfCapsule - (heightOfCapsule * individuali) + 10);
					ownLabel->setText(c2.first, true);

					ownField->setPosition(ownLabel->getPositionX() + ownLabel->getContentWidth() + 20, ownLabel->getPositionY() - 5);
					if (c2.second.second.size() > 4) {
						ownField->setText(c2.second.second, true);
					}
					else {
						ownField->setText(c2.second.second);
					}
					
					ownField->setExitListener([=](const std::string& name, const std::string& current) {
						if (c2.second.first.compare("int") == 0) {
							std::istringstream ss(current);
							int value;

							if (ss >> value) {
								if (value > 0 && value < 20) {
									(*c).second.mapping[std::string(c2.first)] = std::pair<std::string, std::string>(c2.second.first, std::string(current));
								}
								else {
									ownField->setText((*c).second.mapping[std::string(c2.first)].second);
								}
							}
							else {
								ownField->setText((*c).second.mapping[std::string(c2.first)].second);
							}
						}
						else if (c2.second.first.compare("bool") == 0) {
							std::istringstream ss(current);
							int value;

							if (ss >> value) {
								if (value == 0 || value == 1) {
									(*c).second.mapping[std::string(c2.first)] = std::pair<std::string, std::string>(c2.second.first, std::string(current));
								}
								else {
									ownField->setText((*c).second.mapping[std::string(c2.first)].second);
								}
							}
							else {
								ownField->setText((*c).second.mapping[std::string(c2.first)].second);
							}
						}
						else {
							(*c).second.mapping[std::string(c2.first)]  = std::pair<std::string, std::string>(c2.second.first, std::string(current));
						}
					});

					ownField->activate(100 * i + individuali);


					individuali++;
					i++;
				}
			}
			currentTravelled += (drawHeight + (i != yOffset ? separation : 0));
		}

		if (currentTravelled >= (yEnd - yStart) - separation) {
			break;
		}
		i++;
	}
}