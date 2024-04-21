#pragma once
#include "biquad.h"

class BiquadParametric : public Biquad {
public:
    BiquadParametric(float gain_db, float Q, int fc, int fs) {
        construct(gain_db, Q, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float gain_db, float Q, int fc, int fs) = 0;

private:
    void construct(float gain_db, float Q, int fc, int fs) {
        calculate_coeffs(gain_db, Q, fc, fs);
    }
};
