#ifndef _EXCHANGE_BOX_HPP
#define _EXCHANGE_BOX_HPP

#include "../Objects/ModalBox.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class ExchangeBox: public  ModalBox{
    ImageButton up{ObjectInfo<>(WINDOW_WIDTH/17.78f ,WINDOW_HEIGHT/10.f ,WINDOW_WIDTH/80.f ,WINDOW_HEIGHT/2.25f),UP_BUTTON};
    ImageButton down{ObjectInfo<>(WINDOW_WIDTH/17.78f ,WINDOW_HEIGHT/10.f ,WINDOW_WIDTH/8.42f ,WINDOW_HEIGHT/2.25f),DOWN_BUTTON};
    Image zone{ObjectInfo<>(WINDOW_WIDTH/6.4f ,WINDOW_HEIGHT/3.f ,WINDOW_WIDTH/64.f ,WINDOW_HEIGHT/9.f),TEXT_AUCTION};
    ImageButton leave{ObjectInfo<>(WINDOW_WIDTH/10.67f ,WINDOW_HEIGHT/9.f ,WINDOW_WIDTH/21.33f ,WINDOW_HEIGHT/1.384f),LEAVE_BUTTON};
    Text number{ObjectInfo<>(0 ,WINDOW_HEIGHT/15.f ,WINDOW_WIDTH/45.71f ,WINDOW_HEIGHT/4.285f),""};

    int nb = 0;


    public:
        ExchangeBox(ObjectInfo<>info, sf::Color color): AbstractViewObject{info}, ModalBox{info,color}
        {   number.setBold();
            addButtons({&up,&down, &leave});
            addImage(&zone);
            addText(&number);
            background.setHidden();}

        void setTextNumber(int new_number ){
            nb = new_number ;
            number.setString(std::to_string(new_number));
        }

        void upNumber(){this->setTextNumber(nb + 10);}
        void downNumber(){if(nb - 10 >= 0){this->setTextNumber(nb - 10);} }

        int getValidateNumber(){return nb;}

        ImageButton* getUpButton(){return &up;}
        ImageButton* getDownButton(){return &down;}
        ImageButton* getLeaveButton(){return &leave;}
};

#endif