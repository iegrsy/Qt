#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace cv;
using namespace std;

string static getDate() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	string str(buffer);

	return str;
}

void static logFile(string s) {

	string str;

	ifstream infile("error.log");

	string a;
	if (!infile)
	{
		cout << "While opening a file an error is encountered" << endl;
	}
	else
	{
		cout << "File is successfully opened" << endl;
		while (!infile.eof())
		{
			infile >> a;
			str.append(a);
			//cout << a << endl;
		}
	}
	infile.close();

	ofstream myfile("error.log");

	if (myfile.is_open())
	{
		myfile << str.append(s);
		myfile.close();
	}
	else
	{
		cout << "Can not open file.";
	}

}

int main(int, char**)
{
	Mat frame;
	VideoCapture cap;
	cap.open(0);

	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API

	cap.open(deviceID + apiID);

	if (!cap.isOpened())
	{
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	cout << "Start grabbing" << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cerr << "ERROR! blank frame grabbed\n";
			cout << "Camera Error Date: " << getDate() << endl;
			logFile("Camera Error Date: " + getDate() + "\n");
			break;
		}
		imshow("Live", frame);
		waitKey(100);
	}
	return 0;
}

