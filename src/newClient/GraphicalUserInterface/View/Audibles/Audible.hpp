#pragma once
#include <SFML/Audio.hpp>
#include <vector>


template <typename SoundBuffer>
class Audible {

    static inline SoundBuffer buffer;
    static inline std::vector<Audible*> instances;
    sf::Sound sound;

public:
    Audible() { instances.push_back(this); sound.setBuffer(buffer.getBuffer()); }

    void playSound() { sound.play(); }
    static void setVolume(int value) { for (auto* e : instances) e->sound.setVolume(value); }

};


class SoundBuffer {
    sf::SoundBuffer sound_buffer;
protected:
    void loadSound(const std::string &path) { sound_buffer.loadFromFile(path); }
public:
    sf::SoundBuffer &getBuffer() { return sound_buffer; }
};


class ButtonSoundBuffer : public SoundBuffer {
public:
    ButtonSoundBuffer() { loadSound("../assets/sound/click.wav"); }
};
