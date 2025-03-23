#ifndef PLATELOCATE_H
#define PLATELOCATE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class PlateLocate
{
public:
    PlateLocate();
    ~PlateLocate();

    /**
     * @brief 定位车牌在图片中的区域
     * @param src: 待检测车牌原图
     * @param dst_plates: 输出候选车牌向量
     */
    virtual void locate(Mat src, vector<Mat>& dst_plates) = 0;

protected:
    
    /**
     * @brief 验证旋转矩阵rotatedRect是否符合车牌的几何特征
     * @param rotatedRect 输入的旋转矩形
     */
    bool verifySizes(RotatedRect rotatedRect);

    /**
     * @brief 从旋转矩形中提取一个安全的矩形区域，确保该区域不会超出图像边界
     * @param src 输入的图像
     * @param rect 输入的旋转矩形
     * @param safe_rect 输出的安全矩形
     */
    void safeRect(Mat src, RotatedRect rect, Rect2f& safe_rect);
    
    /**
     * @brief 对图像进行旋转校正, 使车牌区域旋转到水平位置
     * @param src 输入的图像
     * @param dst 输出校正后的图像
     * @param rect_size 目标图像的尺寸
     * @param center 旋转的中心点
     * @param angle 旋转角度
     */
	void rotation(Mat src, Mat& dst, Size rect_size, Point2f center, double angle);
	
    /**
     * @brief 对图像中的多个旋转矩形区域进行校正，并提取候选车牌图像保存到dst_plates
     * @param src 输入的图像
     * @param rects 输入的旋转矩形集合
     * @param dst_plates 输出的候选车牌图像集合
     */
    void tortuosity(Mat src, vector<RotatedRect>& rects, vector<Mat>& dst_plates);
};

#endif // PLATELOCATE_H