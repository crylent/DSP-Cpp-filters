#pragma once
#include "biquad.h"

class BiquadBand : public Biquad {
public:
    BiquadBand(float bw, int fc, int fs) {
        construct(bw, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float bw, int fc, int fs) = 0;

    void set_bw(int bw) {
        m_bw = bw;
        recalculate_coeffs();
    }

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_bw, m_fc, m_fs);
    }

private:
    void construct(float bw, int fc, int fs) {
        m_bw = bw;
        m_fc = fc;
        m_fs = fs;
        calculate_coeffs(bw, fc, fs);
    }

    float m_bw;
};
