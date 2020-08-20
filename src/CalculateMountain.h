#include "curl/curl.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"

#ifndef CALCULATEMOUNTAIN_H_
#define CALCULATEMOUNTAIN_H_

using namespace std;

void fillMountain(int *filled, float *prices, int width, int jumpSize) {
	int counter = 0;
	for (int i = 0; i < width / jumpSize; i++) {
		int x = 0;
		float m = (static_cast<int>(prices[i+1]) - static_cast<int>(prices[i])) / jumpSize;
		int b = static_cast<int>(prices[i]);
		for (int j = i; j < i + jumpSize; j++) {
			int val = static_cast<int>(static_cast<float>(x)*m+b);
			filled[counter] = val;
			counter++;
			x++;
		}
	}
}



#endif /* CALCULATEMOUNTAIN_H_ */
