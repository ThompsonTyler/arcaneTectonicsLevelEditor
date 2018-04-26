#pragma once
#include "Components.h"
#include "ComponentType.h"
#include <unordered_map>
#include <string>
#include <cugl/cugl.h>
#include <memory>

class Enemy {
public:
	std::unordered_map<ComponentType, Component> components;
	std::string name;
	std::string baseType;
	std::unordered_map<ComponentType, bool> opened;
	bool needRedraw = false;


	Enemy() : components(), opened() {}
	~Enemy() {}


	template<typename C>
	void addComponent(C component) {
		components[ecs::getComponentType<C>()] = component;
		opened[ecs::getComponentType<C>()] = false;
	}

	void addComponent2(ComponentType type, Component c) {
		components[type] = c;
		opened[type] = false;
	}

	template<typename C>
	void removeComponent() {
		components.erase(ecs::getComponentType<C>());
		opened.erase[ecs::getComponentType<C>()];
	}

	void draw(const std::shared_ptr<cugl::SpriteBatch>& batch, std::vector<std::shared_ptr<cugl::Label>>& labels, std::vector<std::shared_ptr<cugl::Button>>& buttons, float xStart, float xEnd, float yStart, float yEnd, int yOffset);

	void setupLabelFields(std::vector<std::shared_ptr<cugl::Label>>& labels, std::vector<std::shared_ptr<cugl::TextField>>& fields, float xStart, float xEnd, float yStart, float yEnd, int yOffset);
};