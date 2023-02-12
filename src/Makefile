CXX = $(shell [ `g++ -v 2>&1 | grep -o 'version [0-9]\+' | cut -d' ' -f2` -le 9 ] && echo g++-10 || echo g++)
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror=all -D_GNU_SOURCE #-fanalyzer
LDLIBS 	 = -lpthread -lsfml-network -lsfml-system

ifneq ($(shell uname -s), Linux)
	CXXFLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
	LDLIBS   += -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
endif

# Create Client objects
CLIENT_BINS = $(patsubst Client/%.cpp, Client/%.o, $(wildcard Client/*.cpp))

# Create Server objects
SERVER_BINS = $(patsubst Server/%.cpp, Server/%.o, $(wildcard Server/*.cpp))
SERVER_CLIENTMANAGER_BINS = $(patsubst Server/ClientManager/%.cpp, Server/ClientManager/%.o, $(wildcard Server/ClientManager/*.cpp))
SERVER_DATABASE_BINS = $(patsubst Server/Database/%.cpp, Server/Database/%.o, $(wildcard Server/Database/*.cpp))
#SERVER_GAME_BINS = 


.PHONY: default
default: main

.PHONY: clean
clean:
	-rm *.o */*.o */*/*.o 2> /dev/null

rm:
	-rm capitalist server_capitalist 2> /dev/null


main: client server clean

client: ${CLIENT_BINS}
	${CXX} ${CXXFLAGS} -o capitalist $^ ${LDLIBS}

server: ${SERVER_BINS} ${SERVER_CLIENTMANAGER_BINS} ${SERVER_DATABASE_BINS}
	${CXX} ${CXXFLAGS} -o server_capitalist $^ ${LDLIBS}

