
#include "api.h"

int main() {
    const char* imgpath = "/home/jiaopan/Downloads/wifi.jpg";
    init("../config.txt");
    std::cout<<recognizeByFile(imgpath);
}
