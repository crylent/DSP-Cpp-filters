#pragma once
#include "biquad.h"

class BiquadBand : public Biquad {
public:
    virtual tp_coeffs& calculate_coeffs(float bw, float fc, int fs) = 0;

    void set_bw(float bw) {
        m_bw = bw;
        recalculate_coeffs();
    }

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_bw, m_fc, m_fs);
    }

    void handle_set_param(Param param, Numeric value) override {
        if (param == Param::BW) set_bw(value);
        else set_param_error();
    }

    void construct(float bw, float fc, int fs) {
        m_bw = bw;
        m_fc = fc;
        m_fs = fs;
        recalculate_coeffs();
    }

private:
    float m_bw;
};
