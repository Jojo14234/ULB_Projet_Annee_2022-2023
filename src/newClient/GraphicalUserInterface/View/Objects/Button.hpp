/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AbstractViewObject.hpp"


class Button : public virtual AbstractViewObject {
	static inline sf::SoundBuffer soundBuffer;
	static inline bool is_loaded = false;

	static bool loadSound() {
		if (is_loaded) return true;

		soundBuffer.loadFromFile("newclient/GraphicalUserInterface/View/Sound/Walk0.wav") ? is_loaded = true : is_loaded = false;
        return is_loaded;
    }
public:

	explicit Button(ObjectInfo<> info) : AbstractViewObject(info) { Button::loadSound(); }

	virtual void draw(sf::RenderWindow &window) const override = 0;

	template<typename T>
	bool contains(T x, T y) const {
		if (isHidden()) return false;
		// if the click pos is inside the button
		return this->info.getX() <= x && x <= this->info.getX() + this->info.getWidth() &&
			this->info.getY() <= y && y <= this->info.getY() + this->info.getHeight();
	}

	void playSound() {
        sf::Sound sound(soundBuffer);
        sound.play();
    }
};