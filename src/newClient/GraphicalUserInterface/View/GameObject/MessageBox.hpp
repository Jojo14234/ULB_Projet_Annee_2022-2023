#ifndef _MESSAGE_BOX_HPP
#define _MESSAGE_BOX_HPP

#include "../Objects/ModalBox.hpp"
class MessageBox: public ModalBox{
	Text text;
	Text text2;
    public:
        MessageBox(ObjectInfo<> info):  AbstractViewObject(info),ModalBox(info,sf::Color::Magenta)
		,text{ObjectInfo<>(0,24,(info.getX() + 40),info.getY() + info.getHeight() / 3 - 20), ""}
		,text2{ObjectInfo<>(0,24,(info.getX() + 40),info.getY() + info.getHeight() / 3), ""}
		{
			addTexts({&text,&text2});
		}

        void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		for (auto &image : images) image->draw(window);
		for (auto &text : texts) text->draw(window);
		for (auto &button : buttons) button->draw(window);}

	  	void setString(std::string new_string){
			text2.setString("");
			text.setString(new_string);}
		
		void addString(std::string new_string){
			text2.setString(new_string);
		}

		void clearText(){
			text.setString("");
			text2.setString("");
		}


};



#endif