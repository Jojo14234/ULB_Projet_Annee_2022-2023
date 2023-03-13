/**
 * Project Untitled
 */

#pragma once


class AbstractView {

public: 

	AbstractView()=default;

	virtual ~AbstractView()=default;

	virtual void draw()=0;

};