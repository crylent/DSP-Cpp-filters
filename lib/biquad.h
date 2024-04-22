/**
* First order all-pass filter
* Dimitris Tassopoulos 2016
*
* fc, corner frequency
*/

#pragma once

#include <cmath>
#include <functional>

#define COEFF_SIZE_DOUBLE
//#define COEFF_SIZE_FLOAT

#ifndef pi
#define pi  3.1415926535897932384626433832795
#endif

#ifndef sqrt2
#define sqrt2	(2.0 * 0.707106781186547524401)
#endif

#ifndef sqrt2over2
#define sqrt2over2  0.707106781186547524401
#endif

class Biquad {
public:

#ifdef COEFF_SIZE_DOUBLE
    typedef double coef_size_t;
#else
    typedef float coef_size_t;
#endif

    Biquad() : m_xnz1(0), m_xnz2(0), m_ynz1(0), m_ynz2(0), m_offset(0), m_coeffs{0} {};
    virtual ~Biquad() {};

    virtual coef_size_t process(coef_size_t sample)
    {
    	coef_size_t xn = sample;
    	coef_size_t yn = m_coeffs.a0*xn + m_coeffs.a1*m_xnz1 + m_coeffs.a2*m_xnz2
    		            - m_coeffs.b1*m_ynz1 - m_coeffs.b2*m_ynz2;  
    	m_xnz2 = m_xnz1;
    	m_xnz1 = xn;
    	m_ynz2 = m_ynz1;
    	m_ynz1 = yn;    
    	return(yn + m_offset);
    }

	void set_offset(coef_size_t offset)
	{
		m_offset = offset;
	}

	coef_size_t get_offset(void)
	{
		return(m_offset);
	}

    void set_fc(int fc) {
        m_fc = fc;
        recalculate_coeffs();
    }
    void set_fs(int fs) {
        m_fs = fs;
        recalculate_coeffs();
    }

    typedef struct {
    	coef_size_t a0;
    	coef_size_t a1;
    	coef_size_t a2;
    	coef_size_t b1;
    	coef_size_t b2;
    	coef_size_t c0;
    	coef_size_t d0;
    } tp_coeffs;

protected:
    coef_size_t m_xnz1, m_xnz2, m_ynz1, m_ynz2, m_offset;
    tp_coeffs m_coeffs;

    int m_fc, m_fs;

    virtual void recalculate_coeffs() = 0;
};
