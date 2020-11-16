//
// Created by jiaopaner on 2020-10-29.
//

#ifndef OCR_SYSTEM_UTILS_H
#define OCR_SYSTEM_UTILS_H

#endif //OCR_SYSTEM_UTILS_H

#include <opencv2/opencv.hpp>


class utils {
    public:
        static std::string base64Decode(const char* Data, int DataByte);
        static cv::Mat base64ToMat(std::string &base64_data);
};