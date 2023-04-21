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

    std::vector<std::shared_ptr<Image>> alljailcard;
    std::vector<std::shared_ptr<Text>> jail_card_nb;

    std::vector<int> jc_nb {};
    


    public:
        InfoBox(ObjectInfo <>info): AbstractViewObject{info}, Image{info,INFOBOX_PATH}{
            for(int i =0; i< 6; i++){
                pseudo_list.push_back(std::make_shared<Text>(ObjectInfo<>(0,WINDOW_HEIGHT/40.f,info.getX() + WINDOW_WIDTH/53.33f , info.getY() + (i * 60) + WINDOW_HEIGHT/30.f), ""));
                pseudo_list[i]->setBold();
            }
        }
        
        void draw(sf::RenderWindow &window) const override {
            Image::draw(window);
            for (auto money: allmoney){money->draw(window);}
            for (auto& jc: alljailcard){jc->draw(window);}
            for (auto& card: jail_card_nb){card->draw(window);}
            for (auto& pseudo : pseudo_list){pseudo->draw(window);}}

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

                allmoney.push_back(std::make_shared<Money>(ObjectInfo<>(WINDOW_WIDTH/20.f,WINDOW_HEIGHT/22.5f ,info.getX() + WINDOW_WIDTH/10.f, info.getY() + (i * 60) + WINDOW_HEIGHT/30.f), color, start_money));
                }}

        void initJailcard(int n_player, int jail_card){
            for ( int i = 0; i < n_player; i++){

                std::string path;

                if (colorlist[i] == "red"){path = KEYRED_PATH;}
                else if (colorlist[i] == "blue"){path = KEYBLUE_PATH;}
                else if (colorlist[i] == "green"){ path = KEYGREEN_PATH;}
                else if (colorlist[i] == "magenta"){path = KEYMAGENTA_PATH;}
                else if (colorlist[i] == "cyan"){  path = KEYCYAN_PATH;}
                else if (colorlist[i] == "yellow"){ path = KEYYELLOW_PATH;}

                alljailcard.push_back(std::make_shared<Image>(ObjectInfo<>(WINDOW_WIDTH/20.f ,WINDOW_HEIGHT/22.5f ,info.getX() + WINDOW_WIDTH/5.5f , info.getY() + (i * 60) + WINDOW_HEIGHT/30.f), path));
                jail_card_nb.push_back(std::make_shared<Text>(ObjectInfo<>(0,WINDOW_HEIGHT/37.5f ,info.getX() + WINDOW_WIDTH/5.5f , info.getY() + (i * 60) + WINDOW_HEIGHT/30.f), std::to_string(jail_card)));
                jc_nb.push_back(jail_card);
            }
        }

        void addJailCard(int player){setJailCard(player ,jc_nb[player] + 1);}

        void removeJailCard(int player){setJailCard(player ,jc_nb[player] - 1);}

        void setJailCard(int player, int new_jail_card ){jail_card_nb[player]->setString(std::to_string(new_jail_card));}  

        void setPseudo(int player, std::string pseudo){pseudo_list[player]->setString(pseudo);}

        void setMoney( int player, int new_money){allmoney[player]->setMoney(new_money);}

};


#endif