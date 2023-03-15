#The pragma once ensures that this header file is included only once in a program
#pragma once

#The ConstantBlackScholesProcess class  inherits from the QuantLib StochasticProcess1D class.
#include <ql/stochasticprocess.hpp>

namespace QuantLib {

    class ConstantBlackScholesProcess : public StochasticProcess1D {

        // your implementation goes here
        
        
    #The class has four parameters in its constructor (underlyingValue_, riskFreeRate_, volatility_, dividend_), which represent the underlying value of the asset, the risk-free interest rate, the asset's volatility, and the dividend paid on the asset. 
    public:
        ConstantBlackScholesProcess(double underlyingValue_, double riskFreeRate_, double volatility_, double dividend_);

   #The class also has four public methods: xo() , drift(),diffusion(),apply() which we will use in the cpp class
        Real x0() const;
        Real drift(Time t, Real x) const;
        Real diffusion(Time t, Real x) const;
        Real apply(Real x0, Real dx) const;

   # the underlyingValue, riskFreeRate, volatility, and dividend variables are defined in private.
    private:
        double underlyingValue;
        double riskFreeRate;
        double volatility;
        double dividend;

    };

}

