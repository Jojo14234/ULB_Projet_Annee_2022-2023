/**
 * Project Untitled
 */

#pragma once


#include "../AbstractMainWindow.hpp"
#include "AbstractCLI.hpp"
#include "configs.hpp"


class MainCLIWindow : public AbstractMainWindow<STATE, int>, public AbstractCLI {

	void initAttributes() override;

	void draw() override;

public:

    MainCLIWindow();

    ~MainCLIWindow()=default;

    void mainLoop() override;

};