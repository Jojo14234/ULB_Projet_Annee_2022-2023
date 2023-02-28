#ifndef _SERVER_SENTENCES_HPP
#define _SERVER_SENTENCES_HPP

#include <SFML/Network.hpp>
#include <string>


namespace ServerSentences {

	//REGISTER
	std::string REGISTER_REQUEST(std::string s1, std::string s2){ // clientProcessRegister
		return "New register request : " + s1 + " "  + s2;
	}
	const std::string REGISTER_APPROVED = "Register approved";
	const std::string REGISTER_REFUSED = "Register not approved, this Username is already taken";

	//LOGIN
	std::string LOGIN_REQUEST(std::string s1, std::string s2){ // clientProcessRegister
		return "New login request : " + s1 + " "  + s2;
	}
	const std::string LOGIN_APPROVED = "Login approved";
	const std::string LOGIN_REFUSED = "Login not approved";

	std::string receiveQuery(int query, sf::IpAddress ip) { //client loop
		return "Receive: " + std::to_string(query) + " from client: " + ip.toString(); 
	}
	std::string clientLogOut(std::string username) { return " disconnected from his account !"; } // client loop

};

namespace ClientSentence {

	// ANSWER TREATED BY THE CLIENT
	const std::string CLIENT_LOGOUT = "DISCONNECT"; // client process query
	const std::string REGISTER_SUCCEED = "TRUE"; // client process register
	const std::string REGISTER_FAILED = "FALSE"; // client process register
	const std::string LOGIN_SUCCEED = "TRUE";
	const std::string LOGIN_FAILED = "FALSE";


	const std::string ALREADY_CONNECT = "Vous êtes déjà connecté"; // client process register

	//GAME CODE
	const std::string UNKNOWED_GAME = "aucune partie n'existe avec ce code";
	const std::string KNOWED_GAME = "GAME";
	std::string NEW_GAME(int code){
		return "vous avez crée une partie avec le code : " + std::to_string(code);
	}

	// FRIEND INTERACTIONS
	const std::string UNKNOWED_USERNAME = "▌L'utilisateur n'existe pas.";
	const std::string ALREADY_FRIENDS = "▌Vous êtes déjà ami avec cet utilisateur !";
	const std::string ALREADY_SENT_REQUEST = "▌Vous avez déjà envoyé une demandé d'ami a cet utilisateur !";
	const std::string NOT_FRIEND = "▌Vous n'êtes pas ami avec ce joueur !";
	const std::string FRIEND_WITH_HIMSELF = "▌Vous ne pouvez pas être ami avec vous-même.";
	const std::string NO_FRIEND_REQUEST = "▌Cet utilisateur ne vous a pas demandé en ami !";
	const std::string FRIEND_ADD_SUCCEED = "▌La demande d'ami a bien été envoyée !";

	std::string REFUSE_FRIEND_REQUEST(std::string username){
		return "▌Vous avez refusé la demande d'ami de " + username + ".";
	}
	std::string BOTH_FRIEND_REQUEST(std::string username){
		return "▌Cet utilisateur vous avait déjà demandé en ami.\n▌Vous êtes donc désormais ami avec " + username + "!";
	}
	std::string NEW_FRIEND(std::string username){
		return "▌Vous êtes désormais ami avec " + username + ".";
	}
	std::string FRIEND_REMOVE_SUCCEED(std::string username){
		return "▌Vous n'êtes désormais plus ami avec " + username + ".";
	}
}

#endif