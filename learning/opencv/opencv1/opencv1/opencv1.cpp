// opencv1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#define CHAPTER1

using namespace cv;
using namespace std;

//基础操作
int operation1() {
	//图像加载
	Mat src = imread("D:/a.jpg", IMREAD_COLOR);
	//Mat src = imread("D:/a.jpg", IMREAD_GRAYSCALE);
	//Mat src = imread("D:/a.jpg", IMREAD_UNCHANGED);

	if (src.empty()) {
		cout << "empty" << endl;
		return 0;
	}
	Mat output;
	//cvtColor(src, output, COLOR_BGR2GRAY);//色彩空间转换
	//cvtColor(src, output, COLOR_BGR2HSV);//色彩空间转换
	cvtColor(src, output, COLOR_BGR2Luv);//色彩空间转换

	//窗口显示
	//namedWindow("test", CV_WINDOW_AUTOSIZE);
	namedWindow("test", CV_WINDOW_NORMAL);
	imshow("test", src);

	//图像保存
	imwrite("D:/b.jpg", output);
	waitKey(0);
}
//触摸操作
int operation2() {	
	Mat src = imread("D:/a.jpg", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());

	int cols = src.cols*src.channels();
	int startCol = src.channels(); // 第一个像素 【255/0，255/1，255/2】 开始的索引应该是3
	int rows = src.rows;
	int startRow = 1;
	int offsetX = src.channels();

	for (int i = startRow; i < rows-1; ++i) { //第一行和最后一行忽略
		const uchar* previousRow = src.ptr<uchar>(i - 1);
		const uchar* currentRow = src.ptr<uchar>(i);
		const uchar* nextRow = src.ptr<uchar>(i + 1);

		uchar* output = dst.ptr<uchar>(i);
		for (int j = startCol; j < cols - offsetX; ++j) {
			output[j] =saturate_cast<uchar>(5*currentRow[j] -(currentRow[j-offsetX]+currentRow[j+offsetX]+previousRow[j]+nextRow[j]));
		}
	}

	namedWindow("origin", CV_WINDOW_AUTOSIZE);
	namedWindow("changed", CV_WINDOW_NORMAL);

	imshow("origin", src);
	imshow("changed", dst);

	imwrite("D:/b.jpg", dst);
	waitKey(0);
	return 0;
}
//腐蚀
int operation3() {
	Mat src = imread("D:/a.jpg");
	Mat ele = getStructuringElement(MORPH_RECT, Size(100, 100));
	Mat dst;
	erode(src, dst, ele);

	
	imshow("erode", dst);
	waitKey(0);
	return 0;
}
//均值滤波
int operation4() {
	Mat src = imread("D:/a.jpg");
	Mat dst;
	blur(src, dst, Size(15, 15));
	imshow("blur",dst);
	waitKey(0);
	return 0;
}
//边缘检测
int operation5() {
	Mat src = imread("D:/a.jpg");
	Mat gray, edge;

	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, edge, Size(3, 3));
	Canny(edge, edge, 3, 9, 3);
	imshow("canny", edge);
	waitKey(0);
	return 0;
}
//播放视频
int operation6() {
	VideoCapture capture("D:/v.mp4");
	int ct = 0;
	while (ct<250) {
		Mat cap;
		char path[20] = {  };
		
		capture >> cap;
		imshow("show", cap);
		waitKey(60);
		//imwrite(path += ct,cap);
		ct++;
	}
	return 0;
}

int main()
{
#ifdef CHAPTER1
	
	//operation6();



#endif // CHAPTER1


	operation2();
	cout << "no defined" << endl;
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
