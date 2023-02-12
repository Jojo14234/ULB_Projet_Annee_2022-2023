#include "Configs.hpp"

void printMenu() 
{
    std::string text_menu = "—————CAPITALI$T—————\n"
                            "\n"
                            "Pour choisir ce que vous voulez faire sur le jeu, envoyer sur le terminale le numéro qui vous convient.\n"
                            "\n"
                            "1 - Rejoindre une partie.\n"
                            "2 - Crée une partie.\n"
                            "3 - Rank.\n"
                            "4 - Liste d'ami.\n"
                            "5 - Message.\n"
                            "6 - Deconnexion.\n";

    std::cout << text_menu << std::endl;
}


void printStart()
{
    std::string text_start = "—————CAPITALI$T—————\n"
                            "\n"
                            "Pour choisir ce que vous voulez faire sur le jeu, envoyer sur le terminale le numéro qui vous convient.\n"
                            "\n"
                            "1 - Se connecter.\n"
                            "2 - S'enregistrer.\n";

    std::cout << text_start << std::endl;
}