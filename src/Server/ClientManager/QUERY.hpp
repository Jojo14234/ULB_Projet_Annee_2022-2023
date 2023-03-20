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
    PLAYER_JOIN_GAME, // username:gameCode [string]:[int]

    MESSAGE, // All indication message
    USELESS_MESSAGE, // Message useless outside out the terminal app


    INFOS_ROLL_DICE, // dice1:dice2:result:isDouble:doubleCount [int]:[int]:[int]:[bool]:[int]

    INFOS_BUILD_PROP, // All the property name if they are buildable
    INFOS_SELL_BUILD, // All the property name if build can be sell
    INFOS_MORTGAGEABLE_PROP, // All the property mortgageable by a player
    INFOS_LIFT_MORTGAGEABLE_PROP, // All the property lift mortgageable by a player
    INFOS_EXCHANGEABLE_PROP, // username=property_exchangeable:property_exchangeable:|... All teh properties exchangeable by all the player


    INFOS_BUILD_SUCCESS, // property_name (indicate the level up) // TODO add lvl
    INFOS_SELL_BUILD_SUCCESS, // property_name (indicate the level down) // TODO add lvl
    INFOS_MORTGAGE_SUCCESS, // property name of the mortgaged property
    INFOS_LIFT_MORTGAGE_SUCCESS, // property name of the lift mortgaged property
    INFOS_EXCHANGE_SUCCESS, // PropertyName:new_propriétaire nom // Tells that the exchange was successfully made

    INFOS_AUCTION_BID,

    ASK_EXCHANGE, // property_name:price // envoyé au propriétaire de la case pour lui demander si il souhaite accepter l'échange ou non
    ASK_AUCTION, // property_name // envoyé à tout les joueurs pour leur demander de participer à l'enchère
    STOP_WAIT, // Arrête l'échange ou l'enchère en cas de trop longue attente (NE PAS MODIF NI PARSE autrement DANS LE CLIENT)

    DISCONNECT, // Disconnection
    RANKING, // Ranking
    WIN, // username
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
