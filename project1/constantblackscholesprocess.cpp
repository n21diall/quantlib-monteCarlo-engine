
#include "constantblackscholesprocess.hpp"

#include <iostream>

# eulerdiscretization is used to implement the Euler discretization method used in the stochastic process.
#include <ql/processes/eulerdiscretization.hpp> 

namespace QuantLib {
# The class constructor takes four input parameters (underlyingValue_, riskFreeRate_, volatility_, dividend_) representing the underlying value of the asset, risk-free interest rate, asset volatility , and dividend paid on the asset. These parameters are stored in corresponding variables in the class.
   
    ConstantBlackScholesProcess::ConstantBlackScholesProcess(double underlyingValue_, double riskFreeRate_, double volatility_, double dividend_)
        :StochasticProcess1D(ext::make_shared<EulerDiscretization>())
        {
        underlyingValue = underlyingValue_;
        riskFreeRate = riskFreeRate_;
        volatility = volatility_;
        dividend = dividend_;
        }
# The x0() method returns the underlying value of the asset.
    Real ConstantBlackScholesProcess::x0() const {
        return underlyingValue;
    }
# The drift() method calculates the drift of the stochastic process at a given time t and value x.The drift is calculated as the difference between the risk-free interest rate and the dividend, minus half of the squared volatility.
    
    Real ConstantBlackScholesProcess::drift(Time t, Real x) const {
        return riskFreeRate - dividend - 0.5 * volatility * volatility;
    }
#The diffusion() method calculates the volatility of the stochastic process at a given time t and value x.
    Real ConstantBlackScholesProcess::diffusion(Time t, Real x) const {
        return volatility;
    }
# The apply() method calculates the change in the underlying asset value based on a given dx. The method returns the new underlying value calculated by multiplying the initial value x0 by the exponential of dx.
    Real ConstantBlackScholesProcess::apply(Real x0, Real dx) const {
        return x0 * std::exp(dx);
    }

}



