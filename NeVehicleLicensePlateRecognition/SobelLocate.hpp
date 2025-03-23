#ifndef SOBELLOCATE_H
#define SOBELLOCATE_H

#include "PlateLocate.hpp"

class SobelLocate : public PlateLocate
{
public:
	SobelLocate();
	~SobelLocate();

    /**
     * @brief Sobel定位法，定位车牌在图片中的位置区域
     */
	void locate(Mat src, vector<Mat>& dst_plates);
};

#endif // SOBELLOCATE_H