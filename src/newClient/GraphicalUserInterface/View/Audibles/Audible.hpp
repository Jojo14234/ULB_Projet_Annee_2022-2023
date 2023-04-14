#pragma once
#include <SFML/Audio.hpp>

template <typename SoundBuffer>
class Audible {
    static inline SoundBuffer buffer;
    sf::Sound sound;
public:
    Audible() { sound.setBuffer(buffer.getBuffer()); }

    virtual void playSound() { sound.play(); }

    virtual void setVolume(int value) { sound.setVolume(value); }
};


class ButtonSound {
    static inline sf::SoundBuffer sound_buffer;
	static inline bool is_loaded = false;

    static void loadSound() {
		if (is_loaded) return;
		if (sound_buffer.loadFromFile("newclient/GraphicalUserInterface/View/Sound/Walk0.wav")) is_loaded = true;
    }

public:

    ButtonSound() { ButtonSound::loadSound(); }

    static sf::SoundBuffer& getBuffer() { return ButtonSound::sound_buffer; }
};