#ifndef _AUCTION_BOX_HPP
#define _AUCTION_BOX_HPP

#include "../Objects/ModalBox.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class AuctionBox: public  ModalBox{
    ImageButton up{ObjectInfo<>(90,90,20,400),UP_BUTTON};
    ImageButton down{ObjectInfo<>(90,90,190,400),DOWN_BUTTON};
    ImageButton validate{ObjectInfo<>(300,300,0,420),VALIDATE_BUTTON};
    Image zone{ObjectInfo<>(250,300,25,100),TEXT_AUCTION};
    Text number{ObjectInfo<>(0,60,35,210),""};


    public:
        AuctionBox(ObjectInfo<>info, sf::Color color): AbstractViewObject{info}, ModalBox{info,color}
        {   number.setBold();
            addButtons({&up,&down,&validate });
            addImage(&zone);
            addText(&number);}

        void setTextNumber(int new_number ){
            number.setString(std::to_string(new_number));
        }

        ImageButton* getUpButton(){return &up;}
        ImageButton* getDownButton(){return &down;}
        ImageButton* getValidateButton(){return &validate;}
};

#endif