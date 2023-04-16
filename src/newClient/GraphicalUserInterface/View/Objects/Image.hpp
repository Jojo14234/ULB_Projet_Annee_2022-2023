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
	Image()=default;
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

	void rotate(int degrees){
            this->sprite.setRotation(degrees);
            if ((degrees == 90) or (degrees == -90)){
                this->sprite.setScale((this->info.getHeight() )/ (float)texture.getSize().x,(this->info.getWidth() )/ (float)texture.getSize().y);
				this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
				this->sprite.setPosition(this->info.getX() +  this->info.getWidth() / 2.0f, this->info.getY() + this->info.getHeight() / 2.0f);
			}

			else if ((degrees = 180)){
				this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
				this->sprite.setPosition(this->info.getX() +  this->info.getWidth() / 2.0f, this->info.getY() + this->info.getHeight() / 2.0f);}}
		
	/*void setFlag(){
            this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
			this->sprite.setScale(this->info.getWidth()/2 / (float)this->texture.getSize().x, this->info.getHeight()/2 / (float)this->texture.getSize().y);
			this->sprite.setPosition(this->info.getX() +  this->info.getWidth() / 2.0f - this->info.getWidth() / 5.0f , this->info.getY() + this->info.getHeight() / 2.0f - this->info.getHeight() / 5.0f); }*/

	void setPosition(ObjectInfo<> new_info){
		setPosition(new_info.getX(), new_info.getY());
	}

	void setPosition(double x, double y){
		AbstractViewObject::setPosition(x, y);
		this->sprite.setPosition(x, y);
	}

};