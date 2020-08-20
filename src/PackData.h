/*
 * PackData.h
 *
 *  Created on: Aug 19, 2020
 *      Author: jdiniso
 */
#include "curl/curl.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "nlohmann/json.hpp"

#ifndef PACKDATA_H_
#define PACKDATA_H_

using namespace nlohmann;

json toJson(const char* jsonString){
    json jsonObj;
    std::stringstream(jsonString) >> jsonObj;

    return jsonObj;
}


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


void jsonToArr(float *prices, json convert, int size) {
	// Iterates backwards through json
	int i = 0;
//	Creates a copy of the nested object and iterates it backwards, storing them to memory
	json newConvert = convert["Weekly Time Series"];
	for (auto it = newConvert.rbegin(); it != newConvert.rend(); ++it)
	{
		try {
			prices[i] = std::stof(it.value()["1. open"].get_ref<std::string&>());
			i++;
		}
		catch (nlohmann::detail::type_error) {
		}
		if (i > size) {
			break;
		}
	}
}



#endif /* PACKDATA_H_ */
