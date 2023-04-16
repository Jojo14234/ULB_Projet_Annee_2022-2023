#pragma once
#include <SFML/Audio.hpp>


template <typename SoundBuffer>
class Audible {

    static inline SoundBuffer buffer;
    sf::Sound sound;

public:
    Audible() { sound.setBuffer(buffer.getBuffer()); }

    void playSound() { sound.play(); }
    void setVolume(int value) { sound.setVolume(value); }

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
    ButtonSoundBuffer() { loadSound("newclient/GraphicalUserInterface/View/Sound/Walk0.wav"); }
};
