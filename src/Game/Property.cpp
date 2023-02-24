//
// Created by Joachim on 14/02/2023.
//

#include "Property.hpp"

Property::Property(Json:Value prop_info){
	this->status = FREE;
	this->name = prop_info["name"];

	this->color = static_cast<COLOR>(prop_info["color"]);

	this->purchase_price = prop_info["purchase price"];
	this->construct_price = prop_info["construct price"];


	for (int i = 0; i<6; i++){
		this->rent_prices[i] = prop_info["rent prices"][i];
	}

	this->actual_rent_price = rent_prices[static_cast<int>(PROPERTY_LEVEL)]

}