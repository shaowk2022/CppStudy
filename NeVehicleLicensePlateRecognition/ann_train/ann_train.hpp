#ifndef ANNTRAIN_H
#define ANNTRAIN_H

#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include <string>

using namespace std;
using namespace cv;
using namespace ml;

#define ANN_ZH_XML "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann_zh.xml"
#define ANN_XML "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann.xml"
#define ANN_ZH_SAMPLE "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann_zh"
#define ANN_SAMPLE "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann"

struct TrainStruct
{
	string fileName;
	int label;
};

void train();
void train_zh();//训练中文字符

#endif // !ANNTRAIN_H

