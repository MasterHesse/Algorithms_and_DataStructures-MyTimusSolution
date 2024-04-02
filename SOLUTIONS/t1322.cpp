#include <stdio.h>
#include <vector>

std::vector<int> positions[256]; // 存储每个字符的位置
char ciphertext[100001]; // 存储密文
int decrypted[100000], initial_row, position = 0; // 存储解密后的结果，初始行号，解密时的位置

int main() {
    // 读取初始行号和密文
    scanf("%d %s", &initial_row, ciphertext);

    // 遍历密文字符串，将每个字符的索引位置存储在对应字符的vector中
    for (int i = 0; ciphertext[i]; ++i) {
        positions[ciphertext[i]].push_back(i);
    }

    // 将存储位置的数组按照字符顺序存储到解密数组中
    for (int i = 0; i < 256; ++i) {
        for (auto pos : positions[i]) {
            decrypted[position++] = pos;
        }
    }

    // 根据解密后的数组输出原始字符串
    for (int i = 0, current = initial_row - 1; i < position; ++i) {
        putchar(ciphertext[current = decrypted[current]]);
    }

    return 0;
}
