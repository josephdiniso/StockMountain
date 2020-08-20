/*
 * Image.h
 *
 *  Created on: Aug 19, 2020
 *      Author: jdiniso
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <opencv2/opencv.hpp>

using namespace cv;


Vec3f updateColor(Vec3f paintColor, Vec3b finalColor, float jumpSize, int dirs[3]) {
	for (int i = 0; i < 3; i++) {
		if (int (paintColor[i]) != finalColor[i]) {
			paintColor[i] += dirs[i] * jumpSize;
		}
	}
	return paintColor;
}

Vec3b convToInt(Vec3f paintColor) {
	static Vec3b newPaintColor;
	for (int i = 0; i< 3; i++) {
		int newVal = static_cast<uint8_t>(paintColor[i]);
		newPaintColor[i] = newVal;
	}
	return newPaintColor;
}

Mat drawMountain(Mat image, int *points, int width, int height) {
	Vec3b white = {220,220,220};
	Vec3b gray = {60, 61, 74};
	Vec3b black = {35, 35, 35};
	for (int i = width; i >= 0; i--) {
		for (int j = points[i]; j <= height-10; j++) {
			image.at<Vec3b>(Point(i,j)) = white;
		}
		for (int j = points[i]+20; j <= height-10; j++) {
			image.at<Vec3b>(Point(i,j)) = gray;
		}
		for (int j = points[i]+100; j <= height-10; j++) {
			image.at<Vec3b>(Point(i,j)) = black;
		}

	}
	return image;
}

Mat makeGradient(Mat image, Vec3b originalColor, Vec3b finalColor) {
	int dirs[3] = {0,0,0};

	for (int i = 0; i < 3; i++) {
		if (originalColor[i] > finalColor[i]) {
			dirs[i] = -1;
		}
		else {
			dirs[i] = 1;
		}
	}
	Vec3f paintColor = originalColor;
	for (int r = image.rows-10; r > 10; r--) {
		for (int c = 10; c < image.cols-10; c++) {
			image.at<Vec3b>(Point(c,r)) = paintColor;
		}
		paintColor = updateColor(paintColor, finalColor, 0.2, dirs);
	}
	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", image);
	waitKey(0);
	return image;
}



#endif /* IMAGE_H_ */
