#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"
#include "Audibles/Ambiancer.hpp"


class ConnectionGUIController; // forward declaration

class ConnectionGUIView: public AbstractGUIView, public ConnectionAmbiancer {

	// Objects
	Image logo{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f * 145.f/788.f, WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), LOGO_PATH};

	InputBox username{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/10.f), BOX_COLOR, SERIF_FONT_PATH};
	HiddenInputBox password{ObjectInfo<>(WINDOW_WIDTH/3.f, WINDOW_HEIGHT/15.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/6.f, WINDOW_HEIGHT/2.f), BOX_COLOR, SERIF_FONT_PATH};
	Border username_border{username, 5};
	Border password_border{password, 5};

	ImageButton login_button{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 230.f/839.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/4.f - WINDOW_WIDTH/100.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/5.f), LOGIN_BUTTON_PATH};
	ImageButton register_button{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 230.f/839.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/100.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/5.f), REGISTER_BUTTON_PATH};
	ImageButton disconnect_button{ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 230.f/839.f, WINDOW_WIDTH/2.f - WINDOW_WIDTH/8.f , WINDOW_HEIGHT/2.f + ( 2 * WINDOW_HEIGHT/6.f)), DISCONNECT_PATH};

	ModalBox modal_box{ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f, WINDOW_WIDTH/4.f, WINDOW_HEIGHT/4.f), BOX_COLOR};


public:

	explicit ConnectionGUIView(sf::RenderWindow* window);

	~ConnectionGUIView()=default;

	void draw() override;

	void clear();

	friend class ConnectionGUIController;

};