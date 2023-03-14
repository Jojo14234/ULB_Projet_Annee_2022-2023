#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>
#include <SFML/Network.hpp>

#include "InputParser/MainInputParser.hpp"
#include "ClientController.hpp"
#include "./UI/ConnectionUI.hpp"


class Client {

    sf::TcpSocket socket;

    bool connected_to_an_account = false;
    bool in_game = false;

    //int account_id;  //unused

    ClientController controller;
    ConnectionUI ui;

    /*
     * Attempts to connect the `Client` object's socket to the IP address and port specified by the constants `IP` and `PORT`.
     * If the connection attempt is unsuccessful, the method throws a `ConnectServerClientException`.
     */
    void connectToServer();

    /*
     * Disconnect the client from the server by sending a message to it.
     */
    void disconnectFromServer();

    /*
     * Method that attempt to write the MainInputParser parameter `input` on the socket.
     * In function of first element of the MainInputParser objet, it adds one or two parameters on the socket
     * If the methode didn't succeed to write on the socket it throws an error.
     */
    void sendToServer(MainInputParser &input);

    /*
     * Method that attempt to write the GameInputParser parameter `input` on the socket.
     * In function of first element of the GameInputParser objet, it adds one or two parameters on the socket
     * If the methode didn't succeed to write on the socket it throws an error.
     */
    void sendToServer(const GameInputParser &input);

    /*
     * Method that attempt to extract the content of the socket and stores it in the string parameter `output`
     * If the methode didn't succeed to read on the socket it throws an error.
     */
    void receiveFromServer(std::string &output);

    /*
     * Method that return whether or not the connection between an account and a client was made.
     * It also shows the right message in function of the connection and the query (register/login)
     */
    bool checkAccountConnection(std::string &output, QUERY_TYPE query);

    /*
     * Method that attempt to analyse what the server send to the client
     * It returns a string with the interpretation of the server message
     */
    std::string analyseServerResponse(std::string &output);

    /*
     * Executes a loop for handling user input and executing corresponding actions.
     * The method reads the user input and checks its query type, performs necessary actions based on the query type,
     * It returns a boolean value indicating whether to continue the loop or not.
     * If the user input query is for account registration or login and the input parameters are valid,
     *      - creates an `AuthentificationManager` object to validate the input parameters,
     *      - shows an error message if needed,
     *      - sends the input to the server using `sendToServer()` method.
     * If the user input query is to disconnect,
     *      - disconnects from the server using the `disconnectFromServer()` method.
     *      - return false to indicate to stop the loop.
     * If the user input query is invalid or unhandled,
     *      - outputs an error message to the console.
     */
    bool connectionLoop();

    /*
     * Special loop for the client when it enters a game
     * Show message when enters and leave a game
     * Change the `in_game` variable
     */
    void gameLoop();

    /*
     * Loop used during a game to always send message to the server
     */
    void sendToServerLoop();

    /*
     * Loop used during a game to always receive message from the server
     * And performed action based on the message.
     */
    void receiveFromServerLoop();

public:

    /*
     * Constructor of Client.
     * Takes no parameter and try to connect the client object to the server.
     */
    Client() { this->connectToServer(); }

   /*
    * MainLoop of the Client object.
    * It does 3 things :
    * 1. Try to connect the Client to one user account
    * 2. Send message to the server and get response
    * 3. If the response correspond to "GAME" then it launch the gameLoop
    */
    void mainLoop();

};

#endif
