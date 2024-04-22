/**
* Second order band-pass filter
* Dimitris Tassopoulos 2016-2020
*
* fc , corner frequency
* Q , quality factor controlling width of peak or notch = 1/BW
*/
#pragma once
#include "biquad_q.h"

class SO_BPF : public BiquadQ {
public:
    SO_BPF(float Q, float fc, int fs) {
        construct(Q, fc, fs);
    }

    tp_coeffs& calculate_coeffs(float Q, float fc, int fs)
    {
        coef_size_t w = 2.0 * pi * fc / fs;
        coef_size_t b = 0.5*((1.0 - tan(w / (2.0*Q))) / (1.0 + tan(w / (2.0*Q))));
        coef_size_t g = (0.5 + b)*cos(w);
        m_coeffs.a0 = 0.5 - b;
        m_coeffs.a1 = 0.0;
        m_coeffs.a2 = -(0.5 - b);
        m_coeffs.b1 = -2.0 * g;
        m_coeffs.b2 = 2.0 * b;
        return(std::ref(m_coeffs));
    }
};
