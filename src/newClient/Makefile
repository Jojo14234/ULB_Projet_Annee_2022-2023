CXX = $(shell [ `g++ -v 2>&1 | grep -o 'version [0-9]\+' | cut -d' ' -f2` -le 9 ] && echo g++-10 || echo g++)
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic  -D_GNU_SOURCE #-Werror=all
LDLIBS 	 = -lpthread -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system -lncurses

ifneq ($(shell uname -s), Linux)
	CXXFLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
	LDLIBS   += -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
endif


# MODEL
MODEL_BINS = $(patsubst Model/%.cpp, Model/%.o, $(wildcard Model/*.cpp))
MODEL_PARSER_BINS = $(patsubst Model/InputParser/%.cpp, Model/InputParser/%.o, $(wildcard Model/InputParser/*.cpp))

# UI
UI_BINS = $(patsubst UserInterface/%.cpp, UserInterface/%.o, $(wildcard UserInterface/*.cpp))
UI_CONTROLLER_BINS = $(patsubst UserInterface/Controller/%.cpp, UserInterface/Controller/%.o, $(wildcard UserInterface/Controller/*.cpp))
UI_VIEW_BINS = $(patsubst UserInterface/View/%.cpp, UserInterface/View/%.o, $(wildcard UserInterface/View/*.cpp))

# Terminal
TERMINAL_BINS = $(patsubst Terminal/%.cpp, Terminal/%.o, $(wildcard Terminal/*.cpp))
TERMINAL_CONTROLLER_BINS = $(patsubst Terminal/Controller/%.cpp, Terminal/Controller/%.o, $(wildcard Terminal/Controller/*.cpp))
TERMINAL_VIEW_BINS = $(patsubst Terminal/View/%.cpp, Terminal/View/%.o, $(wildcard Terminal/View/*.cpp))



.PHONY: default
default: main

.PHONY: clean
clean:
	-rm *.o */*.o */*/*.o */*/*/*.o 2> /dev/null

rm:
	-rm ../capitalistUI ../capitalistTerminal 2> /dev/null


main: _UI _Terminal clean

_UI: ${UI_BINS} ${UI_CONTROLLER_BINS} ${UI_VIEW_BINS} ${MODEL_BINS} ${MODEL_PARSER_BINS}
	${CXX} ${CXXFLAGS} -o ../capitalistUI $^ ${LDLIBS}

_Terminal: ${TERMINAL_BINS} ${TERMINAL_CONTROLLER_BINS} ${TERMINAL_VIEW_BINS} ${MODEL_BINS} ${MODEL_PARSER_BINS}
	${CXX} ${CXXFLAGS} -o ../capitalistTerminal $^ ${LDLIBS}

UI: _UI clean
Terminal: _Terminal clean