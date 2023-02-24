//
// Created by Joachim on 14/02/2023.
//

#include "Property.hpp"

Property::Property(Json:Value prop_info){
	this->name = prop_info["name"];
	this->purchase_price = prop_info["purchase price"];
	this->construct_price = prop_info["construct price"];
}