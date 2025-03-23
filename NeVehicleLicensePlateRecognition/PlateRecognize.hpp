#ifndef PLATERECOGNIZE_H
#define PLATERECOGNIZE_H

#include "SobelLocate.hpp"
#include "ColorLocate.hpp"
#include "SvmPredict.hpp"
#include "AnnPredict.hpp"

class PlateRecognize
{
public:
	PlateRecognize(const char* svm_model, const char* ann_model, const char* ann_zh_model, const char* cnn_model);
	~PlateRecognize();

	/**
     * @brief 识别车牌内容
	 * @param src 待识别车牌原图
	 * @return 车牌字符串
	 */
	String plateRecognize(Mat src);

private:
	SobelLocate* sobelLocate = 0;
	ColorLocate* colorLocate = 0;
	SvmPredict* svmPredict = 0;
	AnnPredict* annPredict = 0;
};


#endif // PLATERECOGNIZE_H