#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // ���ͷ�ļ�

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 5) { // �����������Ƿ���ȷ
        std::cerr << "Usage: jq.exe input_filename start_address end_address output_filename" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1], std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: �޷��������ļ� " << argv[1] << std::endl;
        return 1;
    }

    fs::path input_path = argv[1];
    uint32_t start_address = std::stoull(argv[2], nullptr, 16);
    uint32_t end_address = std::stoull(argv[3], nullptr, 16);
    fs::path output_path = argv[4];

    std::ofstream output_file(output_path.string(), std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: �޷�������ļ� " << output_path.string() << std::endl;
        return 1;
    }

    input_file.seekg(start_address); // �������ļ�ָ���ƶ�����ʼ��ַ
    char* buffer = new char[end_address - start_address + 1]; // �����ڴ�ռ�
    input_file.read(buffer, end_address - start_address + 1); // ��ȡָ����Χ���ļ����ݵ���������
    output_file.write(buffer, end_address - start_address + 1); // ���������е�����д������ļ���

    delete[] buffer; // �ͷ��ڴ�ռ�
    input_file.close(); // �ر������ļ�
    output_file.close(); // �ر�����ļ�

    std::cout << "�ļ������ѳɹ������� " << output_path.string() << std::endl;
    return 0;
}
