/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"


class Image : AbstractViewObject {

	sf::Texture texture;
	sf::Sprite sprite;

public:

	Image(ObjectInfo<> info, const std::string &path) : AbstractViewObject(info) {
		this->texture.loadFromFile(path);
		this->sprite.setTexture(this->texture);
		this->sprite.setPosition(this->info.getX(), this->info.getY());
		this->sprite.setScale(this->info.getWidth() / this->sprite.getLocalBounds().width, this->info.getHeight() / this->sprite.getLocalBounds().height);
	}

    void draw(sf::RenderWindow& window) const {
        window.draw(this->sprite);
    }

};