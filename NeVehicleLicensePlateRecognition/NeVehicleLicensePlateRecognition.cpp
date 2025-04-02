#include "NeVehicleLicensePlateRecognition.hpp"
#include "PlateRecognize.hpp"
#include "SvmPredict.hpp"

/**
 * 主程序入口
 */
int main(int argc, char* argv[]) {
    if(argc < 2) {
        perror("Usage: ./NeVehicleLicensePlateRecognition <filename>.\n");
        return 0;
    }

    // 车牌图像文件路径
    const char* imgPath = argv[1];

    // svm 和 ann的模型文件路径
    const char* svmXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/resources/svm.xml";
    const char* annXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann.xml";
    const char* annZhXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann_zh.xml";
    // cnn模型路径 使用USE_CNN宏编译来启用CNN进行字母/数字识别
    const char* cnnModelPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/resources/license_plate_cnn.onnx";

    Mat src = imread(imgPath);
    PlateRecognize pr(svmXmlPath,
                      annXmlPath, 
                      annZhXmlPath, 
                      cnnModelPath);
    string str_plate = pr.plateRecognize(src);
    cout << "车牌号识别结果: " << str_plate << endl;
    
    // DEBUG: 让进程等待命令后结束
    waitKey();

    return 0;
}