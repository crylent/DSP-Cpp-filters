#pragma once
#include "biquad.h"

class BiquadQ : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float Q, float fc, int fs) = 0;

    void set_Q(float Q) {
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

    void construct(float Q, float fc, int fs) {
        m_Q = Q;
        m_fc = fc;
        m_fs = fs;
        recalculate_coeffs();
    }

private:
    float m_Q;
};
