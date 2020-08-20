#include "curl/curl.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "nlohmann/json.hpp"
#include "PackData.h"
#include "Image.h"
#include "CalculateMountain.h"

using namespace nlohmann;
using namespace cv;

int main() {
	  CURL *curl;
	  CURLcode res;
	  std::string readBuffer;

	  curl = curl_easy_init();
	  if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.alphavantage.co/query?function=TIME_SERIES_WEEKLY&symbol=TSLA&apikey=PS3ITVUEZVFNKB8N");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		json convert = toJson(readBuffer.c_str());
		int width = 1500;
		int height = 700;
		int jumpSize = 5;
		int size = width / jumpSize;
		float prices[size];
		jsonToArr(&prices[0], convert, size);
		curl_easy_cleanup(curl);


		Mat image = Mat::zeros(Size(width, height), CV_8UC3);
		Vec3b originalColor = {173, 145, 0};
		Vec3b finalColor = {79, 71, 28};
//
//		/*
//		 * TODO:
//		 * Normalize prices to have lowest price at 30% of height and have
//		 * highest price at 60% of height (perhaps use a scale factor equation (?)
//		 */
		int newPrices[width];
		fillMountain(&newPrices[0], &prices[0], width, jumpSize);

//		Core dump from both functions
		Mat newImage = makeGradient(image, originalColor, finalColor);
		newImage = drawMountain(newImage, &newPrices[0], width, height);
		circle( newImage, Point(1400, 100) , 40, Scalar(240,240,240), FILLED, LINE_8);
		namedWindow("img", WINDOW_AUTOSIZE);
		imshow("img", newImage);
		waitKey(0);
		}


	  return 0;
	}
