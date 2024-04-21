#pragma once
#include "biquad.h"

class BiquadParametric : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float gain_db, float Q, int fc, int fs) = 0;
};
