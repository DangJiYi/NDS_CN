#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // 添加头文件

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 5) { // 检查参数数量是否正确
        std::cerr << "Usage: jq.exe input_filename start_address end_address output_filename" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1], std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: 无法打开输入文件 " << argv[1] << std::endl;
        return 1;
    }

    fs::path input_path = argv[1];
    uint32_t start_address = std::stoull(argv[2], nullptr, 16);
    uint32_t end_address = std::stoull(argv[3], nullptr, 16);
    fs::path output_path = argv[4];

    std::ofstream output_file(output_path.string(), std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: 无法打开输出文件 " << output_path.string() << std::endl;
        return 1;
    }

    input_file.seekg(start_address); // 将输入文件指针移动到开始地址
    char* buffer = new char[end_address - start_address + 1]; // 分配内存空间
    input_file.read(buffer, end_address - start_address + 1); // 读取指定范围的文件内容到缓冲区中
    output_file.write(buffer, end_address - start_address + 1); // 将缓冲区中的内容写入输出文件中

    delete[] buffer; // 释放内存空间
    input_file.close(); // 关闭输入文件
    output_file.close(); // 关闭输出文件

    std::cout << "文件内容已成功拷贝到 " << output_path.string() << std::endl;
    return 0;
}
