#pragma once
#include "biquad.h"

class BiquadQ : public Biquad {
public:
    BiquadQ(float Q, int fc, int fs) {
        construct(Q, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float Q, int fc, int fs) = 0;

    void set_Q(int Q) {
        m_Q = Q;
        calculate_coeffs(m_Q, m_fc, m_fs);
    }

    void set_fc(int fc) override {
        m_fc = fc;
        calculate_coeffs(m_Q, m_fc, m_fs);
    }

    void set_fs(int fs) override {
        m_fs = fs;
        calculate_coeffs(m_Q, m_fc, m_fs);
    }

private:
    void construct(float Q, int fc, int fs) {
        m_Q = Q;
        m_fc = fc;
        m_fs = fs;
        calculate_coeffs(Q, fc, fs);
    }

    float m_Q;
};
