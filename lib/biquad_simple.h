#pragma once
#include "biquad.h"

class BiquadSimple : public Biquad {
public:
    BiquadSimple(int fc, int fs) {
        construct(fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(int fc, int fs) = 0;

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_fc, m_fs);
    }

private:
    void construct(int fc, int fs) {
        m_fc = fc;
        m_fs = fs;
        calculate_coeffs(fc, fs);
    }
};
