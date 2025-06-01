#include <iostream>
#include "cnn_block.h"

int main() {
    data_t input[8][8];
    data_t kernel[3][3];
    data_t output[3][3];

    // Initialize input
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            input[i][j] = i + j;

    // Initialize kernel
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            kernel[i][j] = 1.0;

    // Call CNN block
    cnn_block(input, output, kernel);

    // Print result
    std::cout << "Output (3x3 after maxpool):" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            std::cout << output[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}
