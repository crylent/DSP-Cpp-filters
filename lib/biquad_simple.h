#pragma once
#include "biquad.h"

class BiquadSimple : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float fc, int fs) = 0;

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_fc, m_fs);
    }

    void handle_set_param(Param param, Numeric value) override {
        set_param_error();
    }

    void construct(float fc, int fs) {
        m_fc = fc;
        m_fs = fs;
        recalculate_coeffs();
    }
};
