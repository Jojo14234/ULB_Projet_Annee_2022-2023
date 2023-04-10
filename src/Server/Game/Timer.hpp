//
// Created by Joachim on 02/03/2023.
//

#ifndef INFO_F209_GR5_2022_TIMER_HPP
#define INFO_F209_GR5_2022_TIMER_HPP

#include <iostream>
#include <unistd.h>
#include <signal.h>

//TODO AJOUTER SOURCE

// Classe Timer qui implémente un timer en utilisant SIGALRM et pause()
class Timer {
public:
    // Constructeur qui prend en paramètre la durée du timer en secondes
    Timer(int duration) : duration_(duration) {}

    // Méthode Start qui démarre le timer
    void Start() {
        // Configure SIGALRM pour appeler la fonction handler lorsqu'il est reçu
        signal(SIGALRM, &Timer::handler);

        // Définit la durée du timer en utilisant l'alarme d'interruption
        alarm(duration_);

        // Mise en pause du programme jusqu'à ce qu'un signal soit reçu
    }

private:
    // Durée du timer en secondes
    int duration_;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    // Fonction handler qui est appelée lorsqu'un signal SIGALRM est reçu
    static void handler(int sig) {
        // Affiche un message lorsque le timer est terminé
        std::cout << "Timer terminé !" << std::endl;

        // Réinitialise l'alarme d'interruption
        alarm(0);
    }
#pragma GCC diagnostic pop

};

#include <thread>
#include <random>
#include "../ClientManager/ClientManager.hpp"



class Timer2 {
    int seed = 0;
    int duration;
    ClientManager* client;
    std::string stopMessage;

public:
    Timer2(int duration, ClientManager* client, std::string stopMessage): duration{duration} {};

    void start() {
        // 1 il faut créer un autre thread
        std::thread timer_thread(&Timer2::timer, this);
        timer_thread.detach();
    }

    void timer() {
        // 2 il faut générer une seed aléatoire
        std::srand(0);
        int random_seed = std::rand();
        this->seed = random_seed;

        // 2 il faut l'envoyer dans une fonction qui sleep pendant duration sec
        sleep(this->duration);

        // 3 a la fin du thread, on compare si les seed sont toujours identique, auquel cas
        if (this->seed == random_seed) {this->client->sendQueryMsg(this->stopMessage, QUERY::STOP_WAIT);}
    }

    void resetSeed() { this->seed = 0; }

};

#endif //INFO_F209_GR5_2022_TIMER_HPP
