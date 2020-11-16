//
// Created by ALIENWARE on 2020-10-30.
//

#include "cJSON.h"
#include "utils.h"
#include "glog/logging.h"
#include "omp.h"
#include <opencv2/opencv.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

#include <cstring>
#include <fstream>
#include <numeric>

#include <config.h>
#include <ocr_det.h>
#include <ocr_rec.h>


extern "C" {
    /**
    * recognize api
    */
    int init(const char* configFile);
    char* recognizeByBase64(const char* base64_data);
    char* recognizeByFile(const char* file);
}




