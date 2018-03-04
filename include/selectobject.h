#ifndef SELECTOBJECT_H
#define SELECTOBJECT_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

/* maximum number of objects to be tracked */
#define MAX_OBJECTS 1

typedef struct params
{
    Point loc1[MAX_OBJECTS];
    Point loc2[MAX_OBJECTS];
    Mat objects[MAX_OBJECTS];
    string win_name;
    Mat orig_img;
    Mat cur_img;
    int n;
} params;

class selectObject
{
public:
    selectObject();
    int get_regions(Mat frame,vector<Rect>& regions);
private:
};

#endif // SELECTOBJECT_H

