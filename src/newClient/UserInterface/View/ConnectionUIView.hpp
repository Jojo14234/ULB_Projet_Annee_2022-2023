/**
 * Project Untitled
 */

#pragma once

#include "AbstractUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"


class ConnectionUIController; // forward declaration

class ConnectionUIView: public AbstractUIView {

	// Objects
	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), sf::Color(255, 100, 100)};


public:

	explicit ConnectionUIView(sf::RenderWindow* window) : AbstractUIView(window) {
		modal_box.addText(new Text{ObjectInfo<>(0, 80, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), "Welcome to the game!"});
	}

	~ConnectionUIView()=default;

	void draw() override {
		modal_box.draw(*window);
	}

	void clear();

	friend class ConnectionUIController;

};