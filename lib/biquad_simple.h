#pragma once
#include "biquad.h"

class BiquadSimple : public Biquad {
public:
    BiquadSimple(int fc, int fs) {
        construct(fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(int fc, int fs) = 0;

private:
    void construct(int fc, int fs) {
        calculate_coeffs(fc, fs);
    }
};
