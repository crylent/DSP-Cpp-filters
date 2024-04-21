#pragma once
#include "biquad.h"

class BiquadParametric : public Biquad {
public:
    BiquadParametric(float gain_db, float Q, int fc, int fs) {
        construct(gain_db, Q, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float gain_db, float Q, int fc, int fs) = 0;

    void set_gain(int gain_db) {
        m_gain = gain_db;
        calculate_coeffs(m_gain, m_Q, m_fc, m_fs);
    }

    void set_Q(int Q) {
        m_Q = Q;
        calculate_coeffs(m_gain, m_Q, m_fc, m_fs);
    }

    void set_fc(int fc) override {
        m_fc = fc;
        calculate_coeffs(m_gain, m_Q, m_fc, m_fs);
    }

    void set_fs(int fs) override {
        m_fs = fs;
        calculate_coeffs(m_gain, m_Q, m_fc, m_fs);
    }

private:
    void construct(float gain_db, float Q, int fc, int fs) {
        m_gain = gain_db;
        m_Q = Q;
        m_fc = fc;
        m_fs = fs;
        calculate_coeffs(gain_db, Q, fc, fs);
    }

    float m_gain, m_Q;
};
