#ifndef _GAMECODE_BOX_HPP
#define _GAMECODE_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Image.hpp"
#include "../Objects/ObjectInfo.hpp"
#include "../Objects/Text.hpp"


#include "../AssetsPath.hpp"
class GamecodeBox: public Image{
    Text text{ObjectInfo<>(0,24,info.getX() + 100,info.getY() + 90),""};
    public:
        GamecodeBox(ObjectInfo<> info):AbstractViewObject(info), Image(info,GAMECODE){
            text.setBold();
        }
        void draw(sf::RenderWindow &window) const override{
            Image::draw(window);
            text.draw(window);}

        void setGamecode(int gamecode){
            text.setString("GameCode: "+ std::to_string(gamecode));
        }

    

};


#endif