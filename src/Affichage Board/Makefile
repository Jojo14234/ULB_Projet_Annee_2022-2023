FLAGS=-lncurses -Wall -std=c++20

CXXFLAGS = -std=c++20 -lncurses -Wall -Wextra -Wpedantic -Werror=all -D_GNU_SOURCE -fanalyzer -Walloc-zero -Wcast-align \
			-Wdeprecated-copy-dtor -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal \
			-Wformat-signedness -Winit-self -Wlogical-op -Wmismatched-tags -Wnon-virtual-dtor -Wnull-dereference \
			-fdelete-null-pointer-checks -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wsuggest-attribute=cold \
			-Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods \
			-Wsuggest-final-types -Wsuggest-override -Wundef -Wuseless-cast -Wvolatile \
			-Wformat=2  -Wzero-as-null-pointer-constant

#bug avec CXXFLAGS

# Recettes

second_file_cpp=test2.cpp Board_Creator.cpp
second_file_hpp=Board_Creator.hpp common.h


affiche: $(second_file_cpp) $(second_file_hpp)                  
	g++ -std=c++2a $(second_file_cpp) $(second_file_hpp)  -o board $(FLAGS) 