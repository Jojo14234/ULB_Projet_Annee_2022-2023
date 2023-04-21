#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "AbstractViewObject.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Box.hpp"

class TextButton : public Text, public Button, public Box {

public:

    TextButton(ObjectInfo<> info, ObjectInfo<> text_info, const std::string &text, sf::Color text_color=sf::Color::Black, sf::Color box_color=sf::Color::White) : AbstractViewObject(info), Text(text_info, text, text_color), Button(info), Box(info, box_color) {}

    virtual void draw(sf::RenderWindow &window) const override {
        Box::draw(window);
        Text::draw(window);
    }

    void setPosition(double x, double y) override {
        Text::setPosition(x, y);
        Box::setPosition(x, y);
        Button::setPosition(x, y);
    }


};