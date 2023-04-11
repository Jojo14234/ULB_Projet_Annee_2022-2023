#ifndef _MONEY_HPP
#define _MONEY_HPP

#include <string>
#include "../Objects/ModalBox.hpp"

class Money : public virtual ModalBox {
    Text text;
    Image money_im;
    public: 
        Money(ObjectInfo<>info, sf::Color color, int start_money): AbstractViewObject(info),ModalBox(info,color)
        ,money_im(info,MONEY_PATH), text(ObjectInfo<>(0,20,0,0),std::to_string(start_money), sf::Color::White)
        {
            text.setMiddleRect(info);
            text.setThickness(2.0f);
            text.setBold();
            addImage(&money_im);
            addText(&text);}
        
        void draw(sf::RenderWindow &window)  const override{
            if (isHidden()) return;
            Box::draw(window);
            for (auto &image : images) image->draw(window);
            for (auto &text : texts) text->draw(window);
            for (auto &button : buttons) button->draw(window);
        }

        void setMoney(int money){
            text.setString(std::to_string(money));
        }

};


#endif