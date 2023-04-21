#ifndef _AUCTION_BOX_HPP
#define _AUCTION_BOX_HPP

#include "../Objects/ModalBox.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class AuctionBox: public  ModalBox{
    ImageButton up{ObjectInfo<>(WINDOW_WIDTH/17.78f ,WINDOW_HEIGHT/10.f ,WINDOW_WIDTH/80.f ,WINDOW_HEIGHT/2.25),UP_BUTTON};
    ImageButton down{ObjectInfo<>(WINDOW_WIDTH/17.78f ,WINDOW_HEIGHT/10.f ,WINDOW_WIDTH/8.42f ,WINDOW_HEIGHT/2.25),DOWN_BUTTON};
    ImageButton validate{ObjectInfo<>(WINDOW_WIDTH/10.67f ,WINDOW_HEIGHT/6.f ,WINDOW_WIDTH/32.f ,WINDOW_HEIGHT/1.8f),VALIDATE_BUTTON};
    ImageButton leave{ObjectInfo<>(WINDOW_WIDTH/10.67f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/21.33f ,WINDOW_HEIGHT/1.384f),LEAVE_BUTTON};
    Image zone{ObjectInfo<>(WINDOW_WIDTH/6.4f ,WINDOW_HEIGHT/3.f ,WINDOW_WIDTH/64.f ,WINDOW_HEIGHT/9.f),TEXT_AUCTION};
    Text number{ObjectInfo<>(0 ,WINDOW_HEIGHT/15.f ,WINDOW_WIDTH/45.71f ,WINDOW_HEIGHT/4.286f),""};

    int nb = 0;
    int limit = 0;


    public:
        AuctionBox(ObjectInfo<>info, sf::Color color): AbstractViewObject{info}, ModalBox{info,color}
        {   number.setBold();
            addButtons({&up,&down,&validate ,&leave});
            addImage(&zone);
            addText(&number);}

        void setTextNumber(int new_number ){
            nb = new_number+1 ;
            number.setString(std::to_string(nb));
        }

        void setAuctionLimit(int new_number){
            limit = new_number;
        }

        void upNumber(){this->setTextNumber(nb + 50);}
        void downNumber(){if (nb - 50 >= 0 and nb - 50 > limit){ this->setTextNumber(nb - 50);}}

        int getValidateNumber(){return nb;}

        ImageButton* getUpButton(){return &up;}
        ImageButton* getDownButton(){return &down;}
        ImageButton* getValidateButton(){return &validate;}
        ImageButton* getLeaveButton(){return &leave;}
};

#endif