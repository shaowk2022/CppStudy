#ifndef COLORLOCATE_H
#define COLORLOCATE_H

#include "PlateLocate.hpp"

class ColorLocate : public PlateLocate {
public:
    ColorLocate();
    ~ColorLocate();

    /**
     * @brief 颜色定位法，定位车牌在图片中的位置区域
     */
    void locate(Mat src, vector<Mat>& dst_plates);
};

#endif  // COLORLOCATE_H