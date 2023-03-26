/**
 * Project Untitled
 */

#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"


class Image : public virtual AbstractViewObject {

	sf::Texture texture;
	sf::Sprite sprite;

public:

	Image(ObjectInfo<> info, const std::string &path) : AbstractViewObject(info) {
		this->texture.loadFromFile(path);
		this->sprite.setTexture(this->texture);
		this->sprite.setPosition(this->info.getX(), this->info.getY());
		this->sprite.setScale(this->info.getWidth() / (float)this->texture.getSize().x, this->info.getHeight() / (float)this->texture.getSize().y);
	}

    virtual void draw(sf::RenderWindow &window) const override {
	    if (isHidden()) return;
        window.draw(this->sprite);
    }

};