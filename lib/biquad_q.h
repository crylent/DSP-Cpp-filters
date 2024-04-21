#pragma once
#include "biquad.h"

class BiquadQ : public Biquad {
public:
    BiquadQ(float Q, int fc, int fs) {
        construct(Q, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float Q, int fc, int fs) = 0;

private:
    void construct(float Q, int fc, int fs) {
        calculate_coeffs(Q, fc, fs);
    }
};
