//
// Created by ALIENWARE on 2020-10-30.
//

#include "api.h"

using namespace std;
using namespace PaddleOCR;
static DBDetector *det;
static Classifier *cls;
static CRNNRecognizer *rec;

char* recognizeByMat(cv::Mat &image);

int init(const char* configFile){
    Config config(configFile);
    config.PrintConfigInfo();
    det = new DBDetector(config.det_model_dir, config.use_gpu, config.gpu_id, config.gpu_mem,
                             config.cpu_math_library_num_threads, config.use_mkldnn,
                             config.use_zero_copy_run, config.max_side_len, config.det_db_thresh,
                             config.det_db_box_thresh, config.det_db_unclip_ratio, config.visualize);

    if (config.use_angle_cls == true){
        cls = new Classifier(config.cls_model_dir, config.use_gpu, config.gpu_id,
                             config.gpu_mem, config.cpu_math_library_num_threads,
                             config.use_mkldnn, config.use_zero_copy_run,
                             config.cls_thresh);

    };

    rec = new CRNNRecognizer(config.rec_model_dir, config.use_gpu, config.gpu_id,
                           config.gpu_mem, config.cpu_math_library_num_threads,
                           config.use_mkldnn, config.use_zero_copy_run,
                           config.char_list_file);
#ifdef USE_MKL
#pragma omp parallel
    for (auto i = 0; i < 10; i++) {
        LOG_IF(WARNING,
               config.cpu_math_library_num_threads != omp_get_num_threads())
        << "WARNING! MKL is running on " << omp_get_num_threads()
        << " threads while cpu_math_library_num_threads is set to "
        << config.cpu_math_library_num_threads
        << ". Possible reason could be 1. You have set omp_set_num_threads() "
           "somewhere; 2. MKL is not linked properly";
    }
#endif

}

char* recognizeByFile(const char* file) {

    std::string img_path(file);
    cv::Mat image = cv::imread(img_path, cv::IMREAD_COLOR);
    char* result = recognizeByMat(image);
    return result;
}

char* recognizeByBase64(const char* base64_data) {
    std::string data(base64_data);
    cv::Mat image = utils::base64ToMat(data);
    char* result = recognizeByMat(image);
    return result;
}

char* recognizeByMat(cv::Mat &image) {
    try {
        std::vector<std::vector<std::vector<int>>> boxes;
        det->Run(image, boxes);
        return rec->Run(boxes, image, cls);;
    }catch (const char* msg) {
        cJSON* result = cJSON_CreateObject(), * data = cJSON_CreateArray();;
        cJSON_AddNumberToObject(result, "code", 1);
        cJSON_AddStringToObject(result, "msg", msg);
        cJSON_AddItemToObject(result, "data", data);
        return cJSON_PrintUnformatted(result);
    }
}