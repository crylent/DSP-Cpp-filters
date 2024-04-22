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
        recalculate_coeffs();
    }

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_Q, m_fc, m_fs);
    }

    void handle_set_param(Param param, Numeric value) override {
        if (param == Param::Q) set_Q(value);
        else set_param_error();
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
