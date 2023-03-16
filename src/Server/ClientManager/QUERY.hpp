//
// Created by Rémy Ryckeboer on 14/03/2023.
//

#ifndef INFO_F209_GR5_2022_QUERY_HPP
#define INFO_F209_GR5_2022_QUERY_HPP

enum class QUERY {
    FALSE, // BOOL
    TRUE, // BOOL


    INFOS_START, // See sendStartData in GameServer for formatting
    INFOS_GAME, // See sendGameData in GameServer for formatting

    MESSAGE, // All indication message
    USELESS_MESSAGE, // Message useless outside out the terminal app

    PLAYER_JOIN_GAME, // username:gameCode
    WIN, // username



    DISCONNECT, // Disconnection
    RANKING, // Ranking
    ENDGAME, // TO leave the game



    // Refactor
    NOT_N_CURSE_INFOS,// All info not formatted for n-curse
    N_CURSE_INFOS, //All info formatted for n-curse
    START_INFOS, // All start info formatted for n-curse
    STARTING_GAME, // Lancement de la partie
    NOT_STARTED_GAME, // La partie n'est pas encore lancée
    ALREADY_START_GAME, // La partie est déjà en cours
    NOT_ADMIN, // Vous n'êtes pas admin
    SOLO_IN_GAME, // Vous êtes seul dans la partie
    PLAYER_HAS_JOIN_A_GAME, // + nom du joueur
    GAME_CODE, // + game_code(string)
    GO_TO_JAIL, // Vous allez en prison
    ROLL_DICE, // + result 1 : result 2 (string)
    ROLL_DICE_DOUBLE, // + result 1
    ROLL_DICE_BEFORE_END_TURN, // Vous devez jeter les dés avant de finir votre tour.
    NOT_PARTICIPATE_IN_AUCTION, // Une enchère est en cours et vous n'y participez pas !
    PARTICIPATE_IN_AUCTION, // Vous participez à l'enchère
    PARTICIPATE_IN_EXCHANGE, // Vous participez à l'échange
    AUCTION_STARTING, //$$$ AUCTION STARTING $$$
    BEGIN_AUCTION, // + nom de la propriété
    WAIT_BEFORE_AUCTION_BEGIN, // Attention! Comme vous êtes à l'origine de cette enchère, vous participez par défaut. Veuillez attendre " + std::to_string(waiting_time_auction) + " secondes pour que les autres joueurs rejoignent.";
    FINISH_WAITING_TIME, // L'attente est terminé
    AUCTION_TURN, // C'est au tour de '" + player.getClient()->getAccount()->getUsername() + "` d'enchérir ! L'enchère est actuellement à " + std::to_string(bid)
    AUCTION_HOW_TO_BID, //  - Enchérissez pour cette propriété ( /bid [montant] ), - Quittez l'enchère et abandonner la propriété ( /out ) Toute erreur de commande entraine l'exclusion de l'enchère
    HAS_LEAVE_AUCTION_WRONG_CMD, // + nom
    HAS_LEAVE_AUCTION_TO_LOW_BID, // + nom
    HAS_LEAVE_AUCTION_TO_HIGH_BID, // + nom
    AUCTION_NEW_BID, // player.getClient()->getAccount()->getUsername() + " a surenchéri de "; std::to_string(new_bid_i - bid) + "e !";
    WIN_AUCTION, // + nom
    NOT_MY_TURN, // Ce n'est pas à votre tour de jouer
    NO_MORE_COMMAND, // Plus aucune commande ne vous est dispo, votre tour c'est terminé
    COMMAND_INDISPONIBLE, // "Cette commande n'est pas disponible."
    BANKRUPT, // + nom // Afficher msg /participate pour participer
    HAS_BANKRUPT, //  Vous avez fait faillite
    NO_MORE_BANKRUPT, // Vous n'êtes plus en faillite! Continuez votre tour normalement.
    OPTIONS_WHEN_BANKRUPT, // /mortgage, /sell, /give-up
    LOST,
     // Message à afficher
};

#endif //INFO_F209_GR5_2022_QUERY_HPP
