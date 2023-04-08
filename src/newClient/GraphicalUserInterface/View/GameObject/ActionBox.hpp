#ifndef _ACTION_BOX_HPP
#define _ACTION_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class ActionBox: public  Box{
    std::vector<std::shared_ptr<TextButton>> buttons;

    public:
        ActionBox(ObjectInfo<>info, sf::Color color): AbstractViewObject{info}, Box{info,color}{}


        void draw(sf::RenderWindow& window) const override{
            Box::draw(window);
           
            for (auto i : buttons){
                i->draw(window);
            }
        }

        void setButton(std::vector<std::string> action, int text_size ){
            buttons.clear();
            for (int i = 0; i < int(action.size()); i++){
                ObjectInfo<> rect_info(200, 150,50, i *  info.getHeight()/action.size() + 20 );
                buttons.push_back(std::make_shared<TextButton>(rect_info,
                ObjectInfo<>(0,text_size,0,0), "test"));
                buttons[i]->setMiddleRect(rect_info);
            }}

        std::vector<std::shared_ptr<TextButton>> getButtons(){
            return buttons;}
};

#endif