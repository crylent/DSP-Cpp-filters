#pragma once
#include "biquad.h"

class BiquadSimple : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(int fc, int fs) = 0;
};
