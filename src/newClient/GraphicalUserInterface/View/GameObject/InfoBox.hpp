#ifndef _INFO_BOX_HPP
#define _INFO_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Image.hpp"
#include "../Objects/ObjectInfo.hpp"
#include "../Objects/Text.hpp"

#include "Money.hpp"
#include "../AssetsPath.hpp"
class InfoBox: public Image{
    std::vector<std::shared_ptr<Money>> allmoney;
    std::vector<std::string> colorlist {"red","blue","yellow","green","magenta","cyan"};
    std::vector<std::shared_ptr<Text>> pseudo_list;

    Image jail_card {ObjectInfo<> {80,80,info.getX() + 400 - 240  , info.getY() + 350 - 225},OUTJAIL_PATH};

    Text jail_card_nb {ObjectInfo<> {0,20,info.getX() + 400 - 240 + 35  , info.getY() + 350 - 225 + 35},""};

    int card = 0;
    


    public:
        InfoBox(ObjectInfo <>info): AbstractViewObject{info}, Image{info,INFOBOX_PATH}{
            jail_card_nb.setBold();
        }
        
        void draw(sf::RenderWindow &window) const override {
            Image::draw(window);
            for (auto i: allmoney){
                i->draw(window);
            }
            for (auto& j: pseudo_list){
                j->draw(window);}
            
            jail_card.draw(window);
            jail_card_nb.draw(window);
            
            }

        void initMoney( int n_player, int start_money){
            pseudo_list.resize(n_player);
            for ( int i = 0; i < n_player; i++){

                sf::Color color;

                if (colorlist[i] == "red"){color = sf::Color::Red;}
                else if (colorlist[i] == "blue"){color = sf::Color::Blue;}
                else if (colorlist[i] == "green"){ color =  sf::Color::Green;}
                else if (colorlist[i] == "magenta"){color = sf::Color::Magenta;}
                else if (colorlist[i] == "cyan"){ color =  sf::Color::Cyan;}
                else if (colorlist[i] == "yellow"){ color = sf::Color::Yellow;}
                
                if (i < 3){
                    allmoney.push_back(std::make_shared<Money>(ObjectInfo<>(80,40,info.getX() + 400 - 120*(3-i)  , info.getY() + 350 - 110), color, start_money));
                }
                else if ( i >= 3){
                    allmoney.push_back(std::make_shared<Money>(ObjectInfo<>(80,40,info.getX() + 400 - 120*(3-(i - 3))  , info.getY() + 350 - 47), color , start_money));
                }}}
        void setJailCard(int nb_jail_card){
            jail_card_nb.setString(std::to_string(card));
            card = nb_jail_card;
        }

        void addJailCard(){
            setJailCard(card + 1);
        }

        void removeJailCard(){
            if (card - 1 >= 0){
                setJailCard(card - 1);
            }
        }

        void setPseudo(int player, std::string pseudo){
            
            if (player < 3){
                pseudo_list[player] =  std::make_shared<Text>(ObjectInfo<>(0,15,info.getX() + 400 - 120*(3-player) + 3 , info.getY() + 350 - 130), pseudo);
                pseudo_list[player]->setBold();
            }
            else if (player >= 3){
                pseudo_list[player] =  std::make_shared<Text>(ObjectInfo<>(0,15,info.getX() + 400 - 120*(3-(player - 3)) + 3 , info.getY() + 350 - 65), pseudo);
                pseudo_list[player]->setBold();
            }
        }

        void setMoney( int player, int new_money){
            allmoney[player]->setMoney(new_money);}

};


#endif