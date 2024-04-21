#pragma once
#include "biquad.h"

class BiquadQ : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float Q, int fc, int fs) = 0;
};
