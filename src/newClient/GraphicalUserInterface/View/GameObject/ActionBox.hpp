#ifndef _ACTION_BOX_HPP
#define _ACTION_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class ActionBox: public Box{
    std::vector<std::shared_ptr<TextButton>> buttons;

    public:
        ActionBox(ObjectInfo<>info, sf::Color color): Box(info,color), AbstractViewObject(info){}


        void draw(sf::RenderWindow& window) const override{
            Box::draw(window);
           
            for (auto i : buttons){
                i->draw(window);
            }
        }

        void setButton(std::vector<std::string> action, int text_size ){
            buttons.clear();
            for (int i = 0; i < action.size(); i++){
                buttons.push_back(std::make_shared<TextButton>(ObjectInfo<>(200, 150,50, i *  info.getHeight()/action.size() + 20 ),
                ObjectInfo<>(text_size,0,50+200/2,i * (info.getHeight()/action.size() + 20 )+ 50/2), action[i]) );
            }}

        std::vector<std::shared_ptr<TextButton>> getButtons(){
            return buttons;}
};

#endif