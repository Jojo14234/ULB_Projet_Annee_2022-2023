#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "AuthentificationManager.hpp"
#include "../utils/Configs.hpp"
#include "../utils/Exceptions.hpp"
#include "Client.hpp"
#include "InputParser.hpp"


// Public

//////////////////////////////////////////////////////////////////
void Client::connectToServer() {
    if (this->socket.connect(IP, PORT) != sf::Socket::Done) {
        throw ConnectServerClientException();
    }
}

void Client::disconnectFromServer() {
    this->sendToServer(InputParser{"/disconnect"});
    std::string output;
    receiveFromServer(output);
    ui.disconnect();
}

void Client::sendToServer(const InputParser &input) {
    sf::Packet packet;
    packet << static_cast<int>(input.getQueryType());

    switch(input.getQueryType()) {

        case QUERY_TYPE::JOIN_GAME : packet << stoi(input[1]); break;
        case QUERY_TYPE::MESSAGE :	// same as under
        case QUERY_TYPE::LOGIN :    // same as under
        case QUERY_TYPE::REGISTER : packet << input[1] << input[2]; break;
        default : break;
    }
    if (this->socket.send(packet) !=  sf::Socket::Done) { throw WritePipeClientException(); }
}

void Client::receiveFromServer(std::string &output) {
    sf::Packet packet;
    if (this->socket.receive(packet) !=  sf::Socket::Done) { throw ReadPipeClientException(); }
    packet >> output;
}

void Client::mainLoop() {
    while (true) {
        ui.connexionMsg();
        while (not connectedToAnAccount) {
            // Si l'utilisateur à fait /disconnect dans le menu de connexion, cela ferme l'application
            if (!connectionLoop()) {return;}
        }
        while (connectedToAnAccount) {
            std::string input = controller.getNewInput();
            std::cout << "Vous venez de taper : " << input << std::endl;
        }
    }
}

bool Client::connectionLoop() {
    std::string input = controller.getNewInput();
    InputParser parser{input};
    QUERY_TYPE query = parser.getQueryType();

    if ((query == QUERY_TYPE::REGISTER || query == QUERY_TYPE::LOGIN) && parser.getNbParameters() == 2) {
        //check la taille du pseudo et du mdp
        AuthentificationManager authentication{parser[1], parser[2]};
        authentication.showErrorMessage(ui);
        if (!authentication.isValid()) {return true;}
        //envoyer au serveur pour check dans la db

        this->sendToServer(parser);
        std::string output;
        this->receiveFromServer(output);
        connectedToAnAccount = this->checkAccountConnection(output, query);
    }
    //L'utilisateur souhaite quitter l'application
    else if (query == QUERY_TYPE::DISCONNECT) {this->disconnectFromServer(); return false;}
    //L'utilisateur a rentré une mauvaise commande
    else {ui.badConnexionInput();}
    return true;
}

bool Client::checkAccountConnection(std::string &output, QUERY_TYPE query) {
    if (output == "TRUE") {
        (query == QUERY_TYPE::REGISTER) ? ui.acceptRegister() : ui.acceptLogin();
        return true;
    }
    (query == QUERY_TYPE::REGISTER) ? ui.refuseRegister() : ui.refuseLogin();
    return false;
}