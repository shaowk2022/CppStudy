#include "SvmPredict.hpp"

SvmPredict::SvmPredict(const char* svm_model)
{
	svm = SVM::load(svm_model);
	svmHog = new HOGDescriptor(Size(128, 64), Size(16, 16), Size(8, 8), Size(8, 8), 3);
}

SvmPredict::~SvmPredict()
{
	svm->clear();
	svm.release();
	if (svmHog)
	{
		delete svmHog;
		svmHog = 0;
	}
}

void SvmPredict::doPredict(vector<Mat> candi_plates, Mat& final_plate)
{
	Mat plate;
	float score;//svm 评分
	float minScore = FLT_MAX;
	int index = -1;  // 最佳候选车牌的索引
	for (int i = 0; i < candi_plates.size(); i++)
	{
		plate = candi_plates[i];
		//预处理：转为灰度图＋二值化，转为黑白图像便于提取特征
		Mat gray;
		cvtColor(plate, gray, COLOR_BGR2GRAY);
		Mat shold;
		threshold(gray, shold, 0, 255, THRESH_OTSU + THRESH_BINARY);

		// HOG窗口128 x 64, 块大小16x16, cell 8x8, 块步长8x8, 每个方向设置3个bin
		// HOG描述符(Size(128, 64), Size(16, 16), Size(8, 8), Size(8, 8), 3);
		// 提取方向梯度直方图hog特征
		Mat features;
		getHogFeatures(svmHog, shold, features);
		// 提取出的特征重塑为向量(1行n列的矩阵)
		Mat sample = features.reshape(1, 1);
		// 特征向量交给svm 测评，返回评分(越小则越可能是真实车牌)
		score = svm->predict(sample, noArray(), StatModel::Flags::RAW_OUTPUT);
		// printf("svm 候选车牌 %d , 评分是：%f\n", i, score);
		if (score < minScore)
		{
			minScore = score;
			index = i;	// 更新索引指向最佳车牌
		}
		gray.release();

	}
	if (index >= 0)
	{
		final_plate = candi_plates[index].clone();
		// DEBUG
		// imshow("svm最终候选车牌", final_plate);
		// waitKey();
	}
}

void SvmPredict::getHogFeatures(HOGDescriptor* hog, Mat src, Mat& dst)
{
	// 归一化 CV_32S是32位有符号整数
	Mat trainImg = Mat(hog->winSize, CV_32S);
	// 把图片缩放为HOG描述符的窗口大小，这里是128x64, 存到trainImg中
	resize(src, trainImg, hog->winSize); 

	// 计算特征存放到descriptor里
	vector<float> descriptor;
	hog->compute(trainImg, descriptor, hog->winSize);
	// 把特征向量转换为矩阵存储
	Mat feature(descriptor);
	feature.copyTo(dst);  // 存放提取出的特征

	feature.release();
	trainImg.release();

}
