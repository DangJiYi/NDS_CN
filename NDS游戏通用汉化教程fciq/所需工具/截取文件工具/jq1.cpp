#include <iostream>
#include <fstream>
#include <cstddef> // ���ͷ�ļ�

int main(int argc, char* argv[]) {
    if (argc != 5) { // �����������Ƿ���ȷ
        std::cerr << "Usage: jq.exe �����ļ��� ��ʼ��ַ ������ַ ����ļ���" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1], std::ios::binary);
    if (!input_file) {
        std::cerr << "Error: �޷��������ļ� " << argv[1] << std::endl;
        return 1;
    }

    std::streampos start_pos = std::stol(argv[2], nullptr, 16); // ����ʼ��ַ��16����ת��Ϊ����
    std::streampos end_pos = std::stol(argv[3], nullptr, 16); // ��������ַ��16����ת��Ϊ����

    input_file.seekg(start_pos);
    if (input_file.fail()) {
        std::cerr << "Error: �޷���λ����ʼ��ַ " << argv[2] << std::endl;
        return 1;
    }

    std::ofstream output_file(argv[4], std::ios::binary);
    if (!output_file) {
        std::cerr << "Error: �޷�������ļ� " << argv[4] << std::endl;
        return 1;
    }

    char buffer[end_pos-start_pos];
    input_file.read(buffer, sizeof(buffer));
    output_file.write(buffer, input_file.gcount()); // ֻд��ʵ�ʶ�ȡ���ֽ���

    input_file.close();
    output_file.close();

    std::cout << "�ļ������ѳɹ���ȡ�� " << argv[4] << std::endl;
    return 0;
}