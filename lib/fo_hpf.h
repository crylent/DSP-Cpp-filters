/**
* First order high-pass filter
* Dimitris Tassopoulos 2016-2020
*/
#pragma once
#include "biquad_simple.h"

class FO_HPF : public BiquadSimple {
public:
    tp_coeffs& calculate_coeffs(int fc, int fs)
    {
        coef_size_t th = 2.0 * pi * fc / fs;
        coef_size_t g = cos(th) / (1.0 + sin(th));
        m_coeffs.a0 = (1.0 + g) / 2.0;
        m_coeffs.a1 = -((1.0 + g) / 2.0);
        m_coeffs.a2 = 0.0;
        m_coeffs.b1 = -g;
        m_coeffs.b2 = 0.0;
        return(std::ref(m_coeffs));
    }
};
