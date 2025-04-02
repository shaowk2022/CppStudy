#include "ColorLocate.hpp"

ColorLocate::ColorLocate() {
}
ColorLocate::~ColorLocate() {
}

void ColorLocate::locate(Mat src, vector<Mat>& dst_plates) {
    // 1、颜色空间转化为HSV(H是色调，S是饱和度，V是亮度)
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    // 2、寻找蓝色像素，在hsv表示中的范围是：
    // h: 100-124, s: 43-255, v: 46-255
    int channels = hsv.channels();    // 3通道
    int width = hsv.cols * channels;  // 计算每行的像素宽度
    int height = hsv.rows;            // 图像高度
    uchar* p = NULL;

    if (hsv.isContinuous()) {  // 在内存中连续存储则视为一行处理
        width *= height;
        height = 1;
    }

    for (int i = 0; i < height; i++) {
        p = hsv.ptr<uchar>(i);                     // 指向第i行
        for (int j = 0; j < width; j += channels)  // 注意步进是3
        {
            int h = p[j];      // H分量
            int s = p[j + 1];  // S分量
            int v = p[j + 2];  // V分量
            bool isBlue = false;
            if (h >= 100 && h <= 124 &&
                s >= 43 && s <= 255 &&
                v >= 46 && v <= 255) {
                isBlue = true;
            }
            if (isBlue) {  // 把蓝色部分抽离（凸显）高亮
                p[j] = 0;
                p[j + 1] = 0;
                p[j + 2] = 255;  // v值(亮度)拉满
            } else {             // 非蓝色像素点涂黑
                p[j] = 0;
                p[j + 1] = 0;
                p[j + 2] = 0;
            }
        }
    }
    // 分离
    vector<Mat> hsv_split;
    split(hsv, hsv_split);  // 按通道分离为3个
    // 对v通道二值化处理，凸显目标区域方便后续求轮廓，使用OTSU算法自动确定阈值
    Mat shold;
    threshold(hsv_split[2], shold, 0, 255, THRESH_OTSU + THRESH_BINARY);

    // 闭操作
    Mat element = getStructuringElement(MORPH_RECT, Size(17, 3));  // 经验值，可调
    Mat close;
    morphologyEx(shold, close, MORPH_CLOSE, element);  // 填充目标区域中的小孔洞，增强连通性。

    // 求轮廓
    vector<vector<Point>> contours;
    findContours(
        close,             // 输入图像
        contours,          // 输出图像
        RETR_EXTERNAL,     // 取外接轮廓
        CHAIN_APPROX_NONE  // 取轮廓上所有像素点
    );
    vector<RotatedRect> vec_color_rects;
    for (vector<Point> points : contours) {
        // 取最小外接矩形区域
        RotatedRect rotatedRect = minAreaRect(points);
        if (verifySizes(rotatedRect)) {
            vec_color_rects.push_back(rotatedRect);
        }
    }

#if 1
    // DEBUG：在原图上绘制矩形区域
    Mat debugImg = src.clone();  // 复制原图用于绘制
    Scalar color(0, 255, 0);     // 绿色

    for (size_t i = 0; i < vec_color_rects.size(); i++) {
        RotatedRect rect = vec_color_rects[i];
        Point2f vertices[4];
        rect.points(vertices);

        // 绘制旋转矩形
        for (int j = 0; j < 4; j++) {
            line(debugImg, vertices[j], vertices[(j + 1) % 4], color, 2);
        }

        // 可选：标记中心点
        circle(debugImg, rect.center, 3, Scalar(0, 0, 255), -1);

        // 可选：添加编号
        putText(debugImg, to_string(i), rect.center,
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
    }

    imshow("Detected Rectangles", debugImg);

#endif

    // 根据提取出的矩形区域vec_color_rects从原图src中进行裁剪
    tortuosity(src, vec_color_rects, dst_plates);
}
