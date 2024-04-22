/**
* First order all-pass filter
* Dimitris Tassopoulos 2016-2020
*
* fc, corner frequency
*/
#pragma once
#include "biquad_simple.h"

class FO_APF : public BiquadSimple {
    using BiquadSimple::BiquadSimple;

public:

    tp_coeffs& calculate_coeffs(float fc, int fs = 44100)
    {
        coef_size_t a = (tan(pi*fc / fs) - 1.0) / (tan(pi*fc / fs) + 1.0);
        m_coeffs.a0 = a;
        m_coeffs.a1 = 1.0;
        m_coeffs.a2 = 0.0;
        m_coeffs.b1 = a;
        m_coeffs.b2 = 0.0;
        return(std::ref(m_coeffs));
    }
};
