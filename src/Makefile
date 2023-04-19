CXX = $(shell [ `g++ -v 2>&1 | grep -o 'version [0-9]\+' | cut -d' ' -f2` -le 9 ] && echo g++-10 || echo g++)
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror=all -D_GNU_SOURCE
OTHERFLAGS = -fanalyzer -Walloc-zero -Wcast-align \
			-Wdeprecated-copy-dtor -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal \
			-Wformat-signedness -Winit-self -Wlogical-op -Wmismatched-tags -Wnon-virtual-dtor -Wnull-dereference \
			-fdelete-null-pointer-checks -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wsuggest-attribute=cold \
			-Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods \
			-Wsuggest-final-types -Wsuggest-override -Wundef -Wuseless-cast -Wvolatile \
			-Wformat=2  -Wzero-as-null-pointer-constant -fsanitize=address,leak #-Wswitch-default -Wswitch-enum
#CXXFLAGS += ${OTHERFLAGS}
LDLIBS 	 = -lpthread -lsfml-network -lsfml-system -lncurses


ifneq ($(shell uname -s), Linux)
	CXXFLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
	LDLIBS   += -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
endif


# Create Server objects
SERVER_BINS = $(patsubst Server/%.cpp, Server/%.o, $(wildcard Server/*.cpp))
SERVER_CM_BINS = $(patsubst Server/ClientManager/%.cpp, Server/ClientManager/%.o, $(wildcard Server/ClientManager/*.cpp))
SERVER_DB_BINS = $(patsubst Server/Database/%.cpp, Server/Database/%.o, $(wildcard Server/Database/*.cpp))
SERVER_DB_USER = $(patsubst /%.cpp, /%.o, $(wildcard Server/Database/User/*.cpp))
SERVER_DB_FRIEND_BINS = $(patsubst Server/Database/Friend/%.cpp, Server/Database/Friend/%.o, $(wildcard Server/Database/Friend/*.cpp))
SERVER_DB_CHAT_BINS = $(patsubst Server/Database/Chat/%.cpp, Server/Database/Chat/%.o, $(wildcard Server/Database/Chat/*.cpp))
#SERVER_GAME_BINS = $(patsubst Server/Game/%.cpp, Server/Game/%.o, $(wildcard Server/Game/*.cpp))
SERVER_GAME_GAME_SERVER = $(patsubst /%.cpp, /%.o, $(wildcard Server/Game/GameServer/*.cpp))
SERVER_GAME_UTILITY = $(patsubst /%.cpp, /%.o, $(wildcard Server/Game/Utility/*.cpp))
SERVER_HANDLER =  $(patsubst /%.cpp, /%.o, $(wildcard Server/Handler/*.cpp))

# Capitalist
GAME_BINS = $(patsubst Game/%.cpp, Game/%.o, $(wildcard Game/*.cpp))


# GAME
PLAYER_BINS = $(patsubst Game/Player/%.cpp, Game/Player/%.o, $(wildcard Game/Player/*.cpp))
DICE_BINS = $(patsubst Game/Dice/%.cpp, Game/Dice/%.o, $(wildcard Game/Dice/*.cpp))

BOARD_BINS = $(patsubst Game/Board/%.cpp, Game/Board/%.o, $(wildcard Game/Board/*.cpp))
OBTAINABLE_BINS = $(patsubst Game/Board/Obtainable/%.cpp, Game/Board/Obtainable/%.o, $(wildcard Game/Board/Obtainable/*.cpp))
CARDS_BINS = $(patsubst Game/Board/Obtainable/Cards/%.cpp, Game/Board/Obtainable/Cards/%.o, $(wildcard Game/Board/Obtainable/Cards/*.cpp))
CELLS_BINS = $(patsubst Game/Board/Obtainable/Cells/%.cpp, Game/Board/Obtainable/Cells/%.o, $(wildcard Game/Board/Obtainable/Cells/*.cpp))
LAND_BINS = $(patsubst Game/Board/Obtainable/Cells/Land/%.cpp, Game/Board/Obtainable/Cells/Land/%.o, $(wildcard Game/Board/Obtainable/Cells/Land/*.cpp))


#JSON
JSON_BINS = $(patsubst jsoncpp/src/lib_json/%.cpp, jsoncpp/src/lib_json/%.o, $(wildcard jsoncpp/src/lib_json/*.cpp))
JSON_TEST_RUNNER_BINS = $(patsubst jsoncpp/src/jsontestrunner/%.cpp,  jsoncpp/src/jsontestrunner/%.o, $(wildcard jsoncpp/src/jsontestrunner/*.cpp))


.PHONY: default
default: main

.PHONY: clean
clean:
	-rm *.o */*.o */*/*.o */*/*/*.o */*/*/*/*.o */*/*/*/*/*.o 2> /dev/null

rm:
	-rm capitalistCLI capitalistGUI capitalistCUI server_capitalist 2> /dev/null


main: client server

server: ${SERVER_BINS} ${SERVER_CM_BINS} ${SERVER_DB_BINS} ${SERVER_DB_USER} ${GAME_BINS} ${SERVER_GAME_UTILITY} ${SERVER_GAME_GAME_SERVER} ${SERVER_HANDLER} ${PLAYER_BINS} ${DICE_BINS} ${BOARD_BINS}  ${OBTAINABLE_BINS} ${CARDS_BINS} ${CELLS_BINS} ${LAND_BINS} ${SERVER_DB_FRIEND_BINS} ${SERVER_DB_CHAT_BINS} ${SERVER_GAME_BINS} ${JSON_BINS}
	${CXX} ${CXXFLAGS} -o server_capitalist $^ ${LDLIBS}
	make clean

client:
	cd newClient && make

# new Client part
GUI:
	cd newClient && make GUI

CUI:
	cd newClient && make CUI

CLI:
	cd newClient && make CLI
