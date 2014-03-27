// OptimizationCourseHomework1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/**
* Code for thinning a binary image using Zhang-Suen algorithm.
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
* Perform one thinning iteration of Zhang-Suen algorithm
*
* @param  im    Binary image with range = 0-1
* @param  iter  0=even, 1=odd
*/
void thinningIteration(cv::Mat& im, cv::Mat& marker, int iter)
{
	//cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

	for (int i = 1; i < im.rows - 1; i++)
	{
		uchar p2 = im.at<uchar>(i - 1, 1);
		uchar p6 = im.at<uchar>(i + 1, 1);
		uchar p7 = im.at<uchar>(i + 1, 1 - 1);
		uchar p8 = im.at<uchar>(i, 1 - 1);
		uchar p9 = im.at<uchar>(i - 1, 1 - 1);

		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p1 = im.at<uchar>(i, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);

			int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
					(p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
					(p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
					(p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);

			int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;

			int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
			int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

			if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
				marker.at<uchar>(i, j) = 0;

			p9 = p2; p8 = p1; p7 = p6; p2 = p3; p6 = p5; p1 = p4;
		}
	}

	im &= marker;
}

int thinningIteration(cv::Mat& im, cv::Mat& marker)
{
	// iter 0
	int diff = 0;
	for (int i = 1; i < im.rows - 1; i++)
	{
		uchar p2 = im.at<uchar>(i - 1, 1);
		uchar p6 = im.at<uchar>(i + 1, 1);
		uchar p7 = im.at<uchar>(i + 1, 1 - 1);
		uchar p8 = im.at<uchar>(i, 1 - 1);
		uchar p9 = im.at<uchar>(i - 1, 1 - 1);

		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p1 = im.at<uchar>(i, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);

			if (p1)
			{
				int m1 = (p2 * p4 * p6);
				int m2 = (p4 * p6 * p8);

				if (m1 == 0 && m2 == 0)
				{
					int A = (p2 == 0 && p3 != 0) + (p3 == 0 && p4 != 0) +
							(p4 == 0 && p5 != 0) + (p5 == 0 && p6 != 0) +
							(p6 == 0 && p7 != 0) + (p7 == 0 && p8 != 0) +
							(p8 == 0 && p9 != 0) + (p9 == 0 && p2 != 0);

					int B = (p2 + p3) + (p4 + p5) + (p6 + p7) + (p8 + p9);

					if (A == 1 && (B >= 2 && B <= 6))
					{
						diff++;
						marker.at<uchar>(i, j) = 0;
					}
				}
			}

			p9 = p2; p8 = p1; p7 = p6; p2 = p3; p6 = p5; p1 = p4;
		}
	}

	im &= marker;

	// iter 1
	for (int i = 1; i < im.rows - 1; i++)
	{
		uchar p2 = im.at<uchar>(i - 1, 1);
		uchar p6 = im.at<uchar>(i + 1, 1);
		uchar p7 = im.at<uchar>(i + 1, 1 - 1);
		uchar p8 = im.at<uchar>(i, 1 - 1);
		uchar p9 = im.at<uchar>(i - 1, 1 - 1);

		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p1 = im.at<uchar>(i, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);

			if (p1)
			{
				int m1 = (p2 * p4 * p8);
				int m2 = (p2 * p6 * p8);

				if (m1 == 0 && m2 == 0)
				{
					int A = (p2 == 0 && p3 != 0) + (p3 == 0 && p4 != 0) +
							(p4 == 0 && p5 != 0) + (p5 == 0 && p6 != 0) +
							(p6 == 0 && p7 != 0) + (p7 == 0 && p8 != 0) +
							(p8 == 0 && p9 != 0) + (p9 == 0 && p2 != 0);

					int B = (p2 + p3) + (p4 + p5) + (p6 + p7) + (p8 + p9);

					if (A == 1 && (B >= 2 && B <= 6))
					{
						diff++;
						marker.at<uchar>(i, j) = 0;
					}
				}
			}

			p9 = p2; p8 = p1; p7 = p6; p2 = p3; p6 = p5; p1 = p4;
		}
	}

	im &= marker;
	return diff;
}

/**
* Perform one thinning iteration of Guo-Hall algorithm
*
* @param  im    Binary image with range = 0-1
* @param  iter  0=even, 1=odd
*/
void thinningGuoHallIteration(cv::Mat& im, int iter)
{
	cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

	for (int i = 1; i < im.rows - 1; i++)
	{
		for (int j = 1; j < im.cols - 1; j++)
		{
			uchar p2 = im.at<uchar>(i - 1, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);
			uchar p6 = im.at<uchar>(i + 1, j);
			uchar p7 = im.at<uchar>(i + 1, j - 1);
			uchar p8 = im.at<uchar>(i, j - 1);
			uchar p9 = im.at<uchar>(i - 1, j - 1);

			int C = (!p2 & (p3 | p4)) + (!p4 & (p5 | p6)) +
				(!p6 & (p7 | p8)) + (!p8 & (p9 | p2));
			int N1 = (p9 | p2) + (p3 | p4) + (p5 | p6) + (p7 | p8);
			int N2 = (p2 | p3) + (p4 | p5) + (p6 | p7) + (p8 | p9);
			int N = N1 < N2 ? N1 : N2;
			int m = iter == 0 ? ((p6 | p7 | !p9) & p8) : ((p2 | p3 | !p5) & p4);

			if (C == 1 && (N >= 2 && N <= 3) & m == 0)
				marker.at<uchar>(i, j) = 1;
		}
	}

	im &= ~marker;
}


/**
* Function for thinning the given binary image
*
* @param  im  Binary image with range = 0-255
* @param  useGuoHall Use Guo-Hall or Zhang-Suen algorithm
*/
void thinning(cv::Mat& im, bool useGuoHall = false)
{
	im /= 255;

	if (useGuoHall)
	{
		cv::Mat diff;
		cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
		do {
			thinningGuoHallIteration(im, 0);
			thinningGuoHallIteration(im, 1);
			cv::absdiff(im, prev, diff);
			im.copyTo(prev);
		} while (cv::countNonZero(diff) > 0);
	}
	else
	{
		cv::Mat marker = cv::Mat::ones(im.size(), CV_8UC1);
		while (thinningIteration(im, marker) > 0);
	}

	im *= 255;
}

/**
* This is an example on how to call the thinning function above.
*/
int main()
{
	cv::Mat src = cv::imread("../test_image.png");

	if (src.empty())
		return -1;

	cv::Mat bw;
	cv::cvtColor(src, bw, CV_BGR2GRAY);
	cv::threshold(bw, bw, 10, 255, CV_THRESH_BINARY);

	const int N = 30;
	int64 time = 0;
	for (int i = 0; i < N; ++i)
	{
		cv::Mat bb = i < N - 1 ? bw.clone() : bw;
		int64 t = cvGetTickCount();
		thinning(bb, false);
		time += (cvGetTickCount() - t);
	}
	
	printf("%f", time / cvGetTickFrequency() / N);

	//thinning(bw);
	cv::imshow("src", src);
	cv::imshow("dst", bw);
	cv::waitKey(0);

	return 0;
}
