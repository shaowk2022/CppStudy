#include "SobelLocate.hpp"

SobelLocate::SobelLocate() {
}
SobelLocate::~SobelLocate() {
}

void SobelLocate::locate(Mat src, vector<Mat>& dst_plates) {
    // 1、对原图进行高斯模糊
    Mat blur;
    GaussianBlur(src, blur, Size(5, 5), 0);

    // 2、灰度化
    Mat gray;
    cvtColor(blur, gray, COLOR_BGR2GRAY);

    // 3、Sobel运算
    Mat sobel_16;
    // Sobel求导后的导数值可能小于0或者大于255,8位存不下, 用CV_16S
    Sobel(gray, sobel_16, CV_16S, 1, 0);

    // 16位转回8位
    Mat sobel;
    convertScaleAbs(sobel_16, sobel);

    // 4、二值化（正、反两种）
    // 正二值化：适合蓝牌(深底浅字)，
    // 反二值化：适合浅底深字
    Mat shold;
    threshold(sobel, shold, 0, 255, THRESH_OTSU + THRESH_BINARY);

    // 5、形态学操作（闭操作）
    Mat element = getStructuringElement(MORPH_RECT, Size(17, 3));
    Mat close;
    morphologyEx(shold, close, MORPH_CLOSE, element);

    // 6、求出轮廓
    vector<vector<Point>> contours;
    findContours(
        close,             // 输入图像
        contours,          // 输出轮廓
        RETR_EXTERNAL,     // 取外轮廓
        CHAIN_APPROX_NONE  // 取轮廓上所有像素点
    );

    // 存放大小符合要求范围的矩形
    vector<RotatedRect> vec_sobel_rects;
    for (vector<Point> points : contours) {
        // 取最小外接矩形（可旋转/带角度）
        RotatedRect rotatedRect = minAreaRect(points);

        // 7.尺寸判断
        // 初步过滤不符合要求的矩形
        if (verifySizes(rotatedRect)) {
            vec_sobel_rects.push_back(rotatedRect);
        }
    }

    // 校正矩形的角度，并进行标准化
    tortuosity(src, vec_sobel_rects, dst_plates);

    // 释放内存
    blur.release();
    gray.release();
    sobel_16.release();
    sobel.release();
    shold.release();
    element.release();
    close.release();
}