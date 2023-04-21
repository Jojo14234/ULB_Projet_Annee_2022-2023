#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Ambiancer{
    sf::Music music;
    static inline std::vector<Ambiancer*> instances;
    static inline int volume = 50;
public:
    Ambiancer(const std::string& path) { music.openFromFile(path); }
    void playMusic() { if (volume != 0) { music.setVolume(50); music.play(); music.setLoop(true);} }
    void pauseMusic() { music.pause(); }
    void stopMusic() { music.stop(); }
    static void setVolume(int value) { 
        volume = value;
        if (value == 0) { for (auto* e : instances) e->stopMusic(); }
        else { for (auto* e : instances) e->setVolume(value); }
    }
};


struct ConnectionAmbiancer : public Ambiancer {
    ConnectionAmbiancer(): Ambiancer("../assets/sound/redbone.wav"){}
};

struct MenuAmbiancer : public Ambiancer {
    MenuAmbiancer(): Ambiancer("../assets/sound/sandwich.wav"){}
};
