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

# Create Client objects
CLIENT_BINS = $(patsubst Client/%.cpp, Client/%.o, $(wildcard Client/*.cpp))
CLIENT_INPUTPARSER_BINS = $(patsubst Client/InputParser/%.cpp, Client/InputParser/%.o, $(wildcard Client/InputParser/*.cpp))

# Create Ncurses objects
NCURSE_BINS = $(patsubst ClientNcurse/%.cpp, ClientNcurse/%.o, $(wildcard ClientNcurse/*.cpp))
NCURSE_CONTROLLER_BINS = $(patsubst ClientNcurse/Controller/%.cpp, ClientNcurse/Controller/%.o, $(wildcard ClientNcurse/Controller/*.cpp))
NCURSE_VIEW_BINS = $(patsubst ClientNcurse/View/%.cpp, ClientNcurse/View/%.o, $(wildcard ClientNcurse/View/*.cpp))

# Create Server objects
SERVER_BINS = $(patsubst Server/%.cpp, Server/%.o, $(wildcard Server/*.cpp))
SERVER_CM_BINS = $(patsubst Server/ClientManager/%.cpp, Server/ClientManager/%.o, $(wildcard Server/ClientManager/*.cpp))
SERVER_DB_BINS = $(patsubst Server/Database/%.cpp, Server/Database/%.o, $(wildcard Server/Database/*.cpp))
SERVER_DB_FRIEND_BINS = $(patsubst Server/Database/Friend/%.cpp, Server/Database/Friend/%.o, $(wildcard Server/Database/Friend/*.cpp))
SERVER_DB_CHAT_BINS = $(patsubst Server/Database/Chat/%.cpp, Server/Database/Chat/%.o, $(wildcard Server/Database/Chat/*.cpp))
SERVER_GAME_BINS = $(patsubst Server/Game/%.cpp, Server/Game/%.o, $(wildcard Server/Game/*.cpp))

.PHONY: default
default: main

.PHONY: clean
clean:
	-rm *.o */*.o */*/*.o */*/*/*.o 2> /dev/null

rm:
	-rm capitalist server_capitalist ncurse 2> /dev/null


main: client server

client: ${CLIENT_BINS} ${CLIENT_INPUTPARSER_BINS}
	${CXX} ${CXXFLAGS} -o capitalist $^ ${LDLIBS}
	make clean

server: ${SERVER_BINS} ${SERVER_CM_BINS} ${SERVER_DB_BINS} ${SERVER_DB_FRIEND_BINS} ${SERVER_DB_CHAT_BINS} ${SERVER_GAME_BINS}
	${CXX} ${CXXFLAGS} -o server_capitalist $^ ${LDLIBS}
	make clean

ncurse: ${NCURSE_BINS} ${NCURSE_CONTROLLER_BINS} ${NCURSE_VIEW_BINS}
	${CXX} ${CXXFLAGS} -o ncurse $^ ${LDLIBS}
	make clean

