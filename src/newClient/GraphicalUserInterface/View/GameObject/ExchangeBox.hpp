#ifndef _EXCHANGE_BOX_HPP
#define _EXCHANGE_BOX_HPP

#include "../Objects/ModalBox.hpp"
#include "../Objects/TextButton.hpp"


#include <memory>


class ExchangeBox: public  ModalBox{
    ImageButton up{ObjectInfo<>(90,90,20,400),UP_BUTTON};
    ImageButton down{ObjectInfo<>(90,90,190,400),DOWN_BUTTON};
    Image zone{ObjectInfo<>(250,300,25,100),TEXT_AUCTION};
    ImageButton leave{ObjectInfo<>(150,100,75,650),LEAVE_BUTTON};
    Text number{ObjectInfo<>(0,60,35,210),""};

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