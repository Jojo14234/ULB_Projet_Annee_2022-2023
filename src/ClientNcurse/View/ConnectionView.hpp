#ifndef _CONNECTION_VIEW_HPP
#define _CONNECTION_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/InputBox.hpp"
#include "Object/HiddenInputBox.hpp"
#include "Object/Text.hpp"
#include "Object/TextButton.hpp"


class ConnectionView : public AbstractView {

	InputBox username_input_box{ObjectInfo{3, 20, 4, (COLS-20)/2}};
	HiddenInputBox password_input_box{ObjectInfo{3, 20, 9, (COLS-20)/2}};

	Text enter_username{ObjectInfo{3, 20, 2, (COLS-20)/2}, {"Nom d'utilisateur:"}};
	Text enter_password{ObjectInfo{3, 20, 7, (COLS-20)/2}, {"   Mot de passe:"}};

	TextButton login_button{ObjectInfo{3, 20, 13, COLS/2 - 20 -2 }, {"Se connecter"}};
	TextButton register_button{ObjectInfo{3, 20, 13, COLS/2 + 2}, {"Creer un compte"}};

public:

	using AbstractView::AbstractView;
	
	void draw() override {
		username_input_box.draw();
		password_input_box.draw();
        enter_username.draw();
        enter_password.draw();
		login_button.draw();
		register_button.draw();
	}
	
	void clear() {
		this->username_input_box.clear();
		this->password_input_box.clear();
		this->username_input_box.reset();
		this->password_input_box.reset();
	}

	InputBox *getUsernameInputBox() { return &username_input_box; }
	HiddenInputBox *getPasswordInputBox() { return &password_input_box; }

	TextButton *getLoginButton() { return &login_button; }
	TextButton *getRegisterButton() { return &register_button; }

};

#endif
