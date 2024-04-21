#pragma once
#include "biquad.h"

class BiquadBand : public Biquad {
public:
    BiquadBand(float bw, int fc, int fs) {
        construct(bw, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float bw, int fc, int fs) = 0;

private:
    void construct(float bw, int fc, int fs) {
        calculate_coeffs(bw, fc, fs);
    }
};
