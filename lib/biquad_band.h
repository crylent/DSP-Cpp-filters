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
        calculate_coeffs(m_bw, m_fc, m_fs);
    }

    void set_fc(int fc) override {
        m_fc = fc;
        calculate_coeffs(m_bw, m_fc, m_fs);
    }

    void set_fs(int fs) override {
        m_fs = fs;
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
