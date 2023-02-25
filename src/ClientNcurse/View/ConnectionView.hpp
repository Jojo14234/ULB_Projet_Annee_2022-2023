#ifndef _CONNECTION_VIEW_HPP
#define _CONNECTION_VIEW_HPP

#include "AbstractView.hpp"

class ConnectionView : public AbstractView {

private:

	std::string username;
    std::string password;
    int lenght_username = 32;
    int lenght_password = 32;

public:

	using AbstractView::AbstractView;
    ConnectionView(int height, int width, int starty, int startx);
    ~ConnectionView();

	void draw() override {
		// TODO: implement
	}

    void loginUser();
    void registerUser();

};

#endif
