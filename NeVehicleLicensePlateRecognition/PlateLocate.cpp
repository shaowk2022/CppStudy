#include "PlateLocate.hpp"

PlateLocate::PlateLocate() {
}

PlateLocate::~PlateLocate() {
}

bool PlateLocate::verifySizes(RotatedRect rotatedRect) {
    // 容错率
    float error = 0.75f;
    // 理想的车牌宽高比 136/36
    float aspect = float(136) / float(36);
    // 宽高的浮动上下限
    float aspectMin = aspect - aspect * error;
    float aspectMax = aspect + aspect * error;

    // 真实宽高比
    float realAspect = float(rotatedRect.size.width) / float(rotatedRect.size.height);

    // 小于1说明是个竖着的图，需要宽高互换
    if (realAspect < 1)
        realAspect = float(rotatedRect.size.height) / float(rotatedRect.size.width);

    // 计算真实面积
    float area = rotatedRect.size.height * rotatedRect.size.width;

    // 面积的浮动上下限
    int areaMin = 44 * aspect * 14;
    int areaMax = 440 * aspect * 140;

    if ((area < areaMin || area > areaMax) ||
        (realAspect < aspectMin || realAspect > aspectMax))
        return false;
    return true;
}

void PlateLocate::safeRect(Mat src, RotatedRect rect, Rect2f& safe_rect) {
    // RotatedRect无坐标，转换为带坐标的矩形
    Rect2f boudRect = rect.boundingRect2f();

    // 计算安全矩形的左上角坐标, tl是top left
    // 如果boudRect的x和y小于0，则说明截取的矩形超出了左边界或上边界，需设置为0
    float tl_x = boudRect.x > 0 ? boudRect.x : 0;
    float tl_y = boudRect.y > 0 ? boudRect.y : 0;  // x和y从0开始

    // 计算安全矩形的右下角坐标 br是bottom right
    float br_x = (boudRect.x + boudRect.width) < src.cols ? (boudRect.x + boudRect.width - 1)
                                                          : src.cols - 1;  // 判断是否超出右或下边界
    float br_y = (boudRect.y + boudRect.height) < src.rows ? (boudRect.y + boudRect.height - 1)
                                                           : src.rows - 1;

    // 根据左上和右下的最大坐标计算出安全矩形的宽和高
    float w = br_x - tl_x;
    float h = br_y - tl_y;

    // 结果校验
    if (w <= 0 || h <= 0)
        return;

    // 绘制结果矩形区域作为安全矩形
    safe_rect = Rect2f(tl_x, tl_y, w, h);
}

void PlateLocate::rotation(Mat src, Mat& dst, Size rect_size, Point2f center, double angle) {
    // 获得旋转矩阵, 1是缩放因子，1表示不缩放，angle是旋转角度(逆时针为正)
    Mat rot_mat = getRotationMatrix2D(center, angle, 1);

    // NOTE:运用仿射变换: 一种线性变换，包含平移、旋转、缩放和剪切等
    // 它保持图像的“平直性”（直线变换后仍然是直线）和“平行性”（平行线变换后仍然平行）
    Mat mat_rotated;  // 存放变换后的图像

    // 变换后大小可能不一样，但是以对角线作为大小肯定能容纳原图
    int max = sqrt(pow(src.rows, 2) + pow(src.cols, 2));
    // 进行仿射变换，INTER_CUBIC是插值法，计算旋转后像素的值
    warpAffine(src, mat_rotated, rot_mat, Size(max, max), INTER_CUBIC);

    // 截取目标区域，尽量把除车牌外的区域截掉, 结果保存在dst中
    getRectSubPix(mat_rotated, Size(rect_size.width, rect_size.height), center, dst);

    // 释放内存
    mat_rotated.release();
    rot_mat.release();
}

void PlateLocate::tortuosity(Mat src, vector<RotatedRect>& rects, vector<Mat>& dst_plates) {
    // 循环处理矩形
    for (RotatedRect roi_rect : rects) {
        float ratio = (float)roi_rect.size.width / (float)roi_rect.size.height;
        // 宽高比小于1时，说明矩形是竖着的，需要校正矩形的角度
        float roi_angle = roi_rect.angle;
        if (ratio < 1)
            roi_angle = 90 + roi_angle;  // 旋转到水平位置

        // 提取矩形的安全区域
        Rect2f safe_rect;
        safeRect(src, roi_rect, safe_rect);

        // 开始处理候选矩形区域
        // 矩形大小
        Size roi_rect_size = roi_rect.size;
        // 抠图，在src上定位一个Mat, 然后处理
        Mat src_rect = src(safe_rect);  // Mat类型重载了()操作符，所以可以直接用src()

        Mat dst;  // 临时存放处理出的候选车牌

        if (roi_angle - 5 < 0 && roi_angle + 5 > 0) {
            dst = src_rect.clone();  // 倾斜角度较小的，无需旋转, 把定位出的Mat复制给dst
        } else {
            // 对src_rect进行校正
            Point2f roi_ref_center = roi_rect.center - safe_rect.tl();
            Mat rotated_mat;
            // 旋转
            rotation(src_rect, rotated_mat, roi_rect_size, roi_ref_center, roi_angle);
            dst = rotated_mat;
        }

        // 调整图像大小，把校正后的图片固定为36 x 136尺寸
        Mat plate_mat;                       // 存放调整大小后的车牌图像
        plate_mat.create(36, 136, CV_8UC3);  // 绘制一个36x136的RGB图像，CV_8UC3是3通道RGB图像
        // 把dst的内容输出到plate_mat中
        resize(dst, plate_mat, plate_mat.size());

        // 处理好的候选车牌样本放入集合中
        dst_plates.push_back(plate_mat);

        dst.release();
    }
}