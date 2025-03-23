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
    const char* srcPath = argv[1];

    // svm 和 ann的模型文件路径
    const char* svmXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/resources/svm.xml";
    const char* annXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann.xml";
    const char* annZhXmlPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/ann_train/ann_zh.xml";

    // cnn模型路径
    const char* cnnModelPath = "/home/wenke/Study/CppStudy/NeVehicleLicensePlateRecognition/resources/license_plate_cnn.onnx";

    Mat src = imread(srcPath);
    PlateRecognize pr(svmXmlPath, annXmlPath, annZhXmlPath, cnnModelPath);

    // std::locale::global(std::locale("en_US.UTF-8"));
    string str_plate = pr.plateRecognize(src);

    cout << "车牌号识别结果: " << str_plate << endl;
    int key = waitKey(0);
    if(key == 27) return 0;  // 27 是esc的ascii码值
    return 0;
}