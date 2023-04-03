
#pragma once


enum class QUERY {
    FALSEQ, // BOOL
    TRUEQ, // BOOL


    INFOS_START, // See sendStartData in GameServer for formatting
    INFOS_GAME, // See sendGameData in GameServer for formatting

    INFOS_NEW_TURN, // pseudo
    INFOS_PLAYER_MOVE, // username:cell_name:player_money
    INFOS_PLAYER_BOUGHT, // username:cell_name:player_money
    INFOS_PLAYER_DIDNT_BUY, //username
    INFOS_PLAYER_PAID_PLAYER, //amount:loser_index:money:winner_index:money
    INFOS_PLAYER_MOVE_ON_MORTGAGED_CELL, //username:owner_username
    INFOS_PLAYER_MOVE_ON_CARD_CELL, //player:cell_index:description [int]:[int]:[string]
    INFOS_PLAYER_MOVE_ON_TAX_CELL, //tax_name:price:index:player_money
    INFOS_PLAYER_MOVE_ON_OWN_CELL, //username
    INFOS_PLAYER_SEND_TO_PRISON, //username
    INFOS_PLAYER_GO_OUT_PRISON, //username
    INFOS_PLAYER_WON_MONEY, // index:amount:player_money [int]:[int]:[int]
    INFOS_PLAYER_LOSE_MONEY, // index:amount:player_money [int]:[int]:[int]
    //INFOS_PLAYER_MOVE_ON_PARC, //index:amount:player_money

    INFOS_CARD_CELL_TO_GO, // player_index:land_index [int]:[int]
    LOST_GO_OUT_JAIL_CARD, // player_index, informe juste de l'utilisation / la perte d'une carte sortie de prison
    GET_GO_OUT_JAIL_CARD, // player_index, informe de l'événement d'une acquisition d'une carte sortie de prison

    CHOICE_MONEY_CARD, // Informe du choix entre payer ou piocher une carte chance

    INFOS_NOT_ENOUGH_MONEY,
    INFOS_ASK_FOR_PURCHASE, // land_name:land_price [string]:[int]
    INFOS_CARD_DESCRIPTION, // description


    PLAYER_JOIN_GAME, // username:gameCode:nb_player:all_players [string]:[int]:[int]:[string]
    PLAYER_CREATE_GAME, // username:gameCode [string]:[int]

    MESSAGE, // All indication message
    USELESS_MESSAGE, // Message useless outside out the terminal app
    BAD_COMMAND,


    INFOS_ROLL_DICE, // dice1:dice2:result:isDouble:doubleCount [int]:[int]:[int]:[bool]:[int]

    INFOS_LEAVE_BUILD_MODE,
    NO_BUILDABLE_PROP,
    CANNOT_BUILD,

    INFOS_BUILD_PROP, // name:name:... [string]:[string]:... All the property name if they are buildable
    INFOS_SELL_BUILD, // name:name:... [string]:[string]:... All the property name if build can be sell
    INFOS_MORTGAGEABLE_PROP, // All the property mortgageable by a player
    INFOS_LIFT_MORTGAGEABLE_PROP, // All the property lift mortgageable by a player
    INFOS_EXCHANGEABLE_PROP, // username=property_exchangeable:property_exchangeable:|... All teh properties exchangeable by all the player


    INFOS_BUILD_SUCCESS, // property_name:level:mortgaged [string]:[int]:[bool]
    INFOS_SELL_BUILD_SUCCESS, // property_name (indicate the level down) // TODO add lvl
    INFOS_MORTGAGE_SUCCESS, // property name of the mortgaged property
    INFOS_LIFT_MORTGAGE_SUCCESS, // property name of the lift mortgaged property
    INFOS_EXCHANGE_SUCCESS, // PropertyName:new_propriétaire nom // Tells that the exchange was successfully made

    INFOS_AUCTION_BID,

    ASK_EXCHANGE, // property_name:price // envoyé au propriétaire de la case pour lui demander si il souhaite accepter l'échange ou non
    ASK_AUCTION, // property_name // envoyé à tout les joueurs pour leur demander de participer à l'enchère
    STOP_WAIT, // Arrête l'échange ou l'enchère en cas de trop longue attente (NE PAS MODIF NI PARSE autrement DANS LE CLIENT)

    INFOS_DEBT, // amount:username // Montant à rembourser à une joueur [int]:[string], si le username = BANK, c'est qu'il doit de l'argent à la banque

    DISCONNECT, // Disconnection
    RANKING, // Ranking
    WIN, // username
    ENDGAME, // TO leave the game
};
