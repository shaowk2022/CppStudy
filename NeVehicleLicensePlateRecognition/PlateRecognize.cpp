#include "PlateRecognize.hpp"

PlateRecognize::PlateRecognize(const char* svm_model, const char* ann_model, const char* ann_zh_model, const char* cnn_model) {
    sobelLocate = new SobelLocate();
    colorLocate = new ColorLocate();
    svmPredict = new SvmPredict(svm_model);
    annPredict = new AnnPredict(ann_model, ann_zh_model, cnn_model);
}

PlateRecognize::~PlateRecognize() {
    if (sobelLocate) {
        delete sobelLocate;
        sobelLocate = 0;
    }
    if (colorLocate) {
        delete colorLocate;
        colorLocate = 0;
    }
    if (svmPredict) {
        delete svmPredict;
        svmPredict = 0;
    }
    if (annPredict) {
        delete annPredict;
        annPredict = 0;
    }
}

/**
车牌识别（定+检+识）
*/
string PlateRecognize::plateRecognize(Mat src) {
    // 1, 车牌定位

    // NOTE: 关闭sobel定位
    // sobel定位结果：初步筛选的候选车牌向量集
    // vector<Mat> sobel_plates;
    // sobelLocate->locate(src, sobel_plates);

    // 颜色定位
    vector<Mat> color_plates;
    colorLocate->locate(src, color_plates);

    // DEBUG: 这里截取出来的车牌没有问题
    // imshow("sobel_plates", sobel_plates.at(0));
    // imshow("color_plates", color_plates.at(0));
    // waitKey(0);

    // 识别文字
    // 2合1
    vector<Mat> plates;  // 2合1的候选车牌集合

    // plates.insert(plates.end(), sobel_plates.begin(), sobel_plates.end());
    // for(Mat m : sobel_plates) {
    //     m.release();
    // }

    plates.insert(plates.end(), color_plates.begin(), color_plates.end());
    for(Mat m : color_plates) {
        m.release();
    }

    // DEBUG：输出所有候选车牌
    char winName[100];
    for (int i = 0; i < plates.size(); i++)
    {
    	sprintf(winName, "%d候选车牌", i);
    	imshow(winName, plates[i]);
    }

    // 筛选，svm测评
    Mat final_plate;
    svmPredict->doPredict(plates, final_plate);

    // DEBUG: 显示最终车牌
    imshow("final_plate", final_plate);

    string str_plate = annPredict->doPredict(final_plate);

    // DEBUG：这个字符串有问题
    // cout << "PlateRecognize::plateRecognize()车牌号识别结果: " << str_plate << endl;

    return str_plate;
}
