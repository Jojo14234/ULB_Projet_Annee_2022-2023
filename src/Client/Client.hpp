#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser.hpp"


class Client {

	sf::TcpSocket socket;

	// Connect the client to the server
	void connectToServer();

	// Send to server a message to disconnect
	void disconnectToServer();

	// Send a message to the server
	void sendToServer(const InputParser &input);

	// Receive a message from the server
	void receiveFromServer(std::string &output);

    //Connexion loop
    // Renvoie True lors d'une connexion réussie,
    // Renvoie false si l'utilisateur décide de se déconnecter (en gros de quitter le programme ./capitalist)
    bool connexionLoop();

    // Renvoie true si la connexion/création du compte est valide
    // Renvoie false si la connexion/création du compte est invalide
    bool checkAccountConnexion(QUERY_TYPE query);

    bool connectToAccount = false;

public:

	Client() { this->connectToServer(); }

	// Main Loop of the client
	void mainLoop();

};

#endif
