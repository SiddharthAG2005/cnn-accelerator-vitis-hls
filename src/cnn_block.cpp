#include "cnn_block.h"
#include "ap_int.h"
void cnn_block(data_t input[8][8], data_t output[3][3], data_t kernel[3][3]) {
#pragma HLS INTERFACE ap_memory port=input
#pragma HLS INTERFACE ap_memory port=kernel
#pragma HLS INTERFACE ap_memory port=output
#pragma HLS ARRAY_PARTITION variable=kernel complete dim=0
#pragma HLS PIPELINE

    data_t conv_out[6][6];
#pragma HLS ARRAY_PARTITION variable=conv_out complete dim=0

    // Convolution + ReLU
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
#pragma HLS UNROLL factor=2
            data_t sum = 0;
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            conv_out[i][j] = (sum > 0) ? sum : 0; // ReLU
        }
    }

    // Max Pooling (2x2) → 3x3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data_t maxval = conv_out[i*2][j*2];
            for (int m = 0; m < 2; m++) {
                for (int n = 0; n < 2; n++) {
                    data_t val = conv_out[i*2 + m][j*2 + n];
                    if (val > maxval) maxval = val;
                }
            }
            output[i][j] = maxval;
        }
    }
}
