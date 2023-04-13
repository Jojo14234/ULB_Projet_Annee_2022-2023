CXX = $(shell [ `g++ -v 2>&1 | grep -o 'version [0-9]\+' | cut -d' ' -f2` -le 9 ] && echo g++-10 || echo g++)
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -D_GNU_SOURCE #-Werror=all
LDLIBS 	 = -lpthread -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lncurses

ifneq ($(shell uname -s), Linux)
	CXXFLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
	LDLIBS   += -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
endif


# COMMON
MODEL_BINS = $(patsubst Model/%.cpp, Model/%.o, $(wildcard Model/*.cpp))
MODEL_PARSER_BINS = $(patsubst Model/InputParser/%.cpp, Model/InputParser/%.o, $(wildcard Model/InputParser/*.cpp))

# GUI
GUI_BINS = $(patsubst GraphicalUserInterface/%.cpp, GraphicalUserInterface/%.o, $(wildcard GraphicalUserInterface/*.cpp))
GUI_CONTROLLER_BINS = $(patsubst GraphicalUserInterface/Controller/%.cpp, GraphicalUserInterface/Controller/%.o, $(wildcard GraphicalUserInterface/Controller/*.cpp))
GUI_VIEW_BINS = $(patsubst GraphicalUserInterface/View/%.cpp, GraphicalUserInterface/View/%.o, $(wildcard GraphicalUserInterface/View/*.cpp))
GUI_BOARD = $(patsubst GraphicalUserInterface/View/GameObject/%.cpp, GraphicalUserInterface/View/GameObject/%.o, $(wildcard GraphicalUserInterface/View/GameObject/*.cpp))

# CUI
CUI_BINS = $(patsubst CommandUserInterface/%.cpp, CommandUserInterface/%.o, $(wildcard CommandUserInterface/*.cpp))
CUI_CONTROLLER_BINS = $(patsubst CommandUserInterface/Controller/%.cpp, CommandUserInterface/Controller/%.o, $(wildcard CommandUserInterface/Controller/*.cpp))
CUI_VIEW_BINS = $(patsubst CommandUserInterface/View/%.cpp, CommandUserInterface/View/%.o, $(wildcard CommandUserInterface/View/*.cpp))
CUI_GAME_OBJECT_BINS = $(patsubst CommandUserInterface/View/GameObject/%.cpp, CommandUserInterface/View/GameObject/%.o, $(wildcard CommandUserInterface/View/GameObject/*.cpp))

# CLI
CLI_BINS = $(patsubst CommandLineInterface/%.cpp, CommandLineInterface/%.o, $(wildcard CommandLineInterface/*.cpp))
CLI_CONTROLLER_BINS = $(patsubst CommandLineInterface/Controller/%.cpp, CommandLineInterface/Controller/%.o, $(wildcard CommandLineInterface/Controller/*.cpp))
CLI_VIEW_BINS = $(patsubst CommandLineInterface/View/%.cpp, CommandLineInterface/View/%.o, $(wildcard CommandLineInterface/View/*.cpp))




.PHONY: default
default: main

.PHONY: clean
clean:
	-rm *.o */*.o */*/*.o */*/*/*.o 2> /dev/null

rm:
	-rm ../capitalistGUI ../capitalistCUI ../capitalistCLI 2> /dev/null


main: _GUI _CUI _CLI clean

GUI: _GUI clean
CUI: _CUI clean
CLI: _CLI clean


_GUI: ${GUI_BINS} ${GUI_CONTROLLER_BINS} ${GUI_VIEW_BINS} ${GUI_BOARD} ${MODEL_BINS} ${MODEL_PARSER_BINS}
	${CXX} ${CXXFLAGS} -o ../capitalistGUI $^ ${LDLIBS}

_CUI: ${CUI_BINS} ${CUI_CONTROLLER_BINS} ${CUI_VIEW_BINS} ${MODEL_BINS} ${MODEL_PARSER_BINS} ${CUI_GAME_OBJECT_BINS}
	${CXX} ${CXXFLAGS} -o ../capitalistCUI $^ ${LDLIBS}

_CLI: ${CLI_BINS}  ${CLI_CONTROLLER_BINS} ${CLI_VIEW_BINS} ${MODEL_BINS} ${MODEL_PARSER_BINS}
	${CXX} ${CXXFLAGS} -o ../capitalistCLI $^ ${LDLIBS}
