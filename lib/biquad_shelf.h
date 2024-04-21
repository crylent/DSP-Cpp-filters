#pragma once
#include "biquad.h"

class BiquadShelf : public Biquad {
public:
    BiquadShelf(float gain_db, int fc, int fs) {
        construct(gain_db, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float gain_db, int fc, int fs) = 0;

    coef_size_t process(coef_size_t sample)
    {
        coef_size_t xn = sample;
        coef_size_t ynn = m_coeffs.a0*xn + m_coeffs.a1*m_xnz1 + m_coeffs.a2*m_xnz2
            - m_coeffs.b1*m_ynz1 - m_coeffs.b2*m_xnz2;
        coef_size_t yn = m_coeffs.d0*xn + m_coeffs.c0*ynn;

        m_xnz2 = m_xnz1;
        m_xnz1 = xn;
        m_ynz2 = m_ynz1;
        m_ynz1 = yn;
    	return(yn);
    }

private:
    void construct(float gain_db, int fc, int fs) {
        calculate_coeffs(gain_db, fc, fs);
    }
};
