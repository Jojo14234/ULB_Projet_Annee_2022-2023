#ifndef _MESSAGE_BOX_HPP
#define _MESSAGE_BOX_HPP

#include "../Objects/ModalBox.hpp"
class MessageBox: public ModalBox{
	Text text;
    public:
        MessageBox(ObjectInfo<> info):  AbstractViewObject(info),ModalBox(info,sf::Color::Magenta)
		,text{ObjectInfo<>(0,24,(info.getX() + (info.getWidth() / 3)),info.getY() + info.getHeight() / 3), ""}
		{
			addText(&text);
		}

        void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		for (auto &image : images) image->draw(window);
		for (auto &text : texts) text->draw(window);
		for (auto &button : buttons) button->draw(window);}

	  	void setString(std::string new_string){
			text.setString(new_string);}

		void clearText(){
			text.setString("");
		}


};



#endif