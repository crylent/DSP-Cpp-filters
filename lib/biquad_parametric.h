#pragma once
#include "biquad.h"

class BiquadParametric : public Biquad {
public:
    BiquadParametric(float gain_db, float Q, float fc, int fs) {
        construct(gain_db, Q, fc, fs);
    }

    virtual tp_coeffs& calculate_coeffs(float gain_db, float Q, float fc, int fs) = 0;

    void set_gain(float gain_db) {
        m_gain = gain_db;
        recalculate_coeffs();
    }

    void set_Q(float Q) {
        m_Q = Q;
        recalculate_coeffs();
    }

protected:
    void recalculate_coeffs() override {
        calculate_coeffs(m_gain, m_Q, m_fc, m_fs);
    }

    void handle_set_param(Param param, Numeric value) override {
        if (param == Param::GAIN) set_gain(value);
        else if (param == Param::Q) set_Q(value);
        else set_param_error();
    }

private:
    void construct(float gain_db, float Q, float fc, int fs) {
        m_gain = gain_db;
        m_Q = Q;
        m_fc = fc;
        m_fs = fs;
        calculate_coeffs(gain_db, Q, fc, fs);
    }

    float m_gain, m_Q;
};
