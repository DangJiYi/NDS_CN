#include <iostream>
#include <fstream>
#include <cstddef> // 添加头文件

int main(int argc, char* argv[]) {
    if (argc != 5) { // 检查参数数量是否正确
        std::cerr << "Usage: jq.exe 输入文件名 开始地址 结束地址 输出文件名" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1], std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: 无法打开输入文件 " << argv[1] << std::endl;
        return 1;
    }

    std::streampos start_pos = std::stol(argv[2], nullptr, 16); // 将开始地址从16进制转换为整数
    std::streampos end_pos = std::stol(argv[3], nullptr, 16); // 将结束地址从16进制转换为整数

    input_file.seekg(start_pos);
    if (input_file.fail()) {
        std::cerr << "Error: 无法定位到开始地址 " << argv[2] << std::endl;
        return 1;
    }

    std::ofstream output_file(argv[4], std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: 无法打开输出文件 " << argv[4] << std::endl;
        return 1;
    }

    char buffer[end_pos-start_pos];
    input_file.read(buffer, sizeof(buffer));
    output_file.write(buffer, input_file.gcount()); // 只写入实际读取的字节数

    input_file.close();
    output_file.close();

    std::cout << "文件内容已成功截取到 " << argv[4] << std::endl;
    return 0;
}