//
// Created by Joachim on 14/02/2023.
//

#include "Property.hpp"

Property::Property(){
    Json::Value root;
	Json::Reader reader;
	std::ifstream file("data/card_data.json");
	if (not reader.parse(file, root)) { perror("Error parsing file"); return; }
}