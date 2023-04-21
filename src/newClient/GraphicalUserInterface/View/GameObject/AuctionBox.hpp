#ifndef _AUCTION_BOX_HPP
#define _AUCTION_BOX_HPP

#include "../Objects/ModalBox.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class AuctionBox: public  ModalBox{
    ImageButton up{ObjectInfo<>(90,90,20,400),UP_BUTTON};
    ImageButton down{ObjectInfo<>(90,90,190,400),DOWN_BUTTON};
    ImageButton validate{ObjectInfo<>(150,150,50,500),VALIDATE_BUTTON};
    ImageButton leave{ObjectInfo<>(150,100,75,650),LEAVE_BUTTON};
    Image zone{ObjectInfo<>(250,300,25,100),TEXT_AUCTION};
    Text number{ObjectInfo<>(0,60,35,210),""};

    int nb = 0;
    int limit = 0;


    public:
        AuctionBox(ObjectInfo<>info, sf::Color color): AbstractViewObject{info}, ModalBox{info,color}
        {   number.setBold();
            addButtons({&up,&down,&validate ,&leave});
            addImage(&zone);
            addText(&number);}

        void setTextNumber(int new_number ){
            nb = new_number ;
            number.setString(std::to_string(new_number));
        }

        void setAuctionLimit(int new_number){
            limit = new_number;
        }

        void upNumber(){this->setTextNumber(nb + 50);}
        void downNumber(){if (nb - 50 >= 0 and nb - 50 >= limit){ this->setTextNumber(nb - 50);}}

        int getValidateNumber(){return nb;}

        ImageButton* getUpButton(){return &up;}
        ImageButton* getDownButton(){return &down;}
        ImageButton* getValidateButton(){return &validate;}
        ImageButton* getLeaveButton(){return &leave;}
};

#endif