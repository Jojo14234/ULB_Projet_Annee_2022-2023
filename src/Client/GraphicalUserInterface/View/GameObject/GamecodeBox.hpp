#ifndef _GAMECODE_BOX_HPP
#define _GAMECODE_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Image.hpp"
#include "../Objects/ObjectInfo.hpp"
#include "../Objects/Text.hpp"


#include "../AssetsPath.hpp"
class GamecodeBox: public Image{
    Text text{ObjectInfo<>(0,24,info.getX() + WINDOW_WIDTH/21.33f, info.getY() + WINDOW_HEIGHT/12.f),""};
    public:
        GamecodeBox(ObjectInfo<> info):AbstractViewObject(info), Image(info,GAMECODE){
            text.setBold();
        }
        void draw(sf::RenderWindow &window) const override{
            Image::draw(window);
            text.draw(window);}

        void setGamecode(int gamecode){
            std::cout << "ici " << info.getX() << " "<< info.getY() << " "<< info.getHeight() << std::endl; 
            text.setString("GameCode: "+ std::to_string(gamecode));
        }

    

};


#endif