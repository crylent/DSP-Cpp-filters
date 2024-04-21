#pragma once
#include "biquad.h"

class BiquadButterworth : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float bw, int fc, int fs) = 0;
};
