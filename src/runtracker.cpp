#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"
#include <dirent.h>


#include "selectobject.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{

	/*
	 *5个参数，是否使用HOG特征，是否使用fixed_window,是否使用single-scale,是否显示，是否使用lab,是否gray
	 */
	if (argc > 5)
		return -1;

	bool HOG = true;
	bool FIXEDWINDOW = true;
	bool MULTISCALE = true;
	bool SILENT = false;
	bool LAB = false;

	for(int i = 0; i < argc; i++)
	{
		if ( strcmp (argv[i], "hog") == 0 )
			HOG = true;
		if ( strcmp (argv[i], "fixed_window") == 0 )
			FIXEDWINDOW = true;
		if ( strcmp (argv[i], "singlescale") == 0 )
			MULTISCALE = false;
		if ( strcmp (argv[i], "show") == 0 )
			SILENT = false;
		if ( strcmp (argv[i], "lab") == 0 ){
			LAB = true;
			HOG = true;
		}
		if ( strcmp (argv[i], "gray") == 0 )
			HOG = false;
	}
	cout<<HOG<<"	"<<FIXEDWINDOW<<"	"<<MULTISCALE<<"	"<<SILENT<<"	"<<LAB<<"	"<<endl;
	// Create KCFTracker object
	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);

	// Frame readed
	Mat frame;

	// Tracker results
	Rect result;

	/*// Path to list.txt
	ifstream listFile;
	string fileName = "images.txt";
  	listFile.open(fileName);

  	// Read groundtruth for the 1st frame
  	ifstream groundtruthFile;
	string groundtruth = "region.txt";
  	groundtruthFile.open(groundtruth);
  	string firstLine;
  	getline(groundtruthFile, firstLine);
	groundtruthFile.close();
  	
  	istringstream ss(firstLine);

  	// Read groundtruth like a dumb
  	float x1, y1, x2, y2, x3, y3, x4, y4;
  	char ch;
	ss >> x1;
	ss >> ch;
	ss >> y1;
	ss >> ch;
	ss >> x2;
	ss >> ch;
	ss >> y2;
	ss >> ch;
	ss >> x3;
	ss >> ch;
	ss >> y3;
	ss >> ch;
	ss >> x4;
	ss >> ch;
	ss >> y4; 

	// Using min and max of X and Y for groundtruth rectangle
	float xMin =  min(x1, min(x2, min(x3, x4)));
	float yMin =  min(y1, min(y2, min(y3, y4)));
	float width = max(x1, max(x2, max(x3, x4))) - xMin;
	float height = max(y1, max(y2, max(y3, y4))) - yMin;

	
	// Read Images
	ifstream listFramesFile;
	string listFrames = "images.txt";
	listFramesFile.open(listFrames);
	string frameName;


	// Write Results
	ofstream resultsFile;
	string resultsPath = "output.txt";
	resultsFile.open(resultsPath);

	// Frame counter
	int nFrames = 0;

	VideoCapture video("/home/renjing/dataSet/soccer.avi");
	if(!video.isOpened())
		cout<<"video open error"<<endl;
		//while ( getline(listFramesFile, frameName) )
	xMin=230;
	yMin=150;
	width=107;
	height=169;*/
    VideoCapture video("/home/ren/work/bgslibrary-build/data/IMG_0357.MOV");//("/home/renjing/dataSet/soccer.avi");
	if(!video.isOpened())
		cout<<"video open error"<<endl;
	float xMin;
	float yMin;
	float width;
	float height;
	double sum=0;
	int nFrames = 0,num_objects=0;
	selectObject sO;
	Rect regions;
	while(1)
	{
		//frameName = frameName;

		// Read each frame from the list
		//frame = imread(frameName, CV_LOAD_IMAGE_COLOR);
		video>>frame;
		if(frame.empty())
			break;
		double t = (double)getTickCount();
		// First frame, give the groundtruth to the tracker
		if (num_objects == 0)
		{
			cout<<"Select object region to track\n"<<endl;
			vector<Rect> regions;
			//while(num_objects == 0 )
			//{
				num_objects = sO.get_regions(frame, regions);
			//}
			if(num_objects!=0)
			{
				xMin=regions[0].x;
				yMin=regions[0].y;
				width=regions[0].width;
				height=regions[0].height;
				tracker.init( Rect(xMin, yMin, width, height), frame );
				rectangle( frame, Point( xMin, yMin ), Point( xMin+width, yMin+height), Scalar( 0, 255, 255 ), 1, 8 );
				//resultsFile << xMin << "," << yMin << "," << width << "," << height << endl;
			}
		}
		// Update
		else
		{
			if(num_objects!=0)
			{
				result = tracker.update(frame);
				rectangle( frame, Point( result.x, result.y ), Point( result.x+result.width, result.y+result.height), Scalar( 0, 255, 255 ), 1, 8 );
			}//resultsFile << result.x << "," << result.y << "," << result.width << "," << result.height << endl;
		}
		t = ((double)getTickCount() - t) / getTickFrequency();
		cout << t << endl;
		sum+=t;
		nFrames++;

		if (!SILENT&&num_objects!=0)
		{
			imshow("Image", frame);
            char c=waitKey(30);
            if(c=='s')
            {
                waitKey(0);
            }
            if(c=='q')
            {
                return 1;
            }
		}
	}
	double ave=sum/(double)nFrames;
	cout<<"ave:"<<ave<<endl;
	//resultsFile.close();

}
