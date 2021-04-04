
#include <ql/qldefines.hpp>
#ifdef BOOST_MSVC
#  include <ql/auto_link.hpp>
#endif
#include "constantblackscholesprocess.hpp"
#include "mceuropeanengine.hpp"
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/payoffs.hpp>
#include <ql/exercise.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/termstructures/yield/zerocurve.hpp>
#include <ql/termstructures/volatility/equityfx/blackvariancecurve.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <iostream>
#include <chrono>

using namespace QuantLib;

int main() {

    try {

        // modify the sample code below to suit your project

        Calendar calendar = TARGET();
        Date today = Date(24, February, 2021);
        Settings::instance().evaluationDate() = today;

        Option::Type type(Option::Put);
        Real underlying = 36;
        Real strike = 40;
        Date maturity(24, May, 2021);

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));
        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

        Handle<Quote> underlyingH(ext::make_shared<SimpleQuote>(underlying));

        DayCounter dayCounter = Actual365Fixed();
        Handle<YieldTermStructure> riskFreeRate(
            ext::shared_ptr<YieldTermStructure>(
                new ZeroCurve({ today, today + 6 * Months }, { 0.01, 0.015 }, dayCounter)));
        Handle<BlackVolTermStructure> volatility(
            ext::shared_ptr<BlackVolTermStructure>(
                new BlackVarianceCurve(today, { today + 3 * Months, today + 6 * Months }, { 0.20, 0.25 }, dayCounter)));

        ext::shared_ptr<BlackScholesProcess> bsmProcess(
            new BlackScholesProcess(underlyingH, riskFreeRate, volatility));

        // options
        VanillaOption europeanOption(payoff, europeanExercise);

        bool isConstantBS = true;
        Size timeSteps = 1;
        Size mcSeed = 42;
        Size n_samples = 10;

        int power_max_time_steps = 3;
        int power_max_n_samples = 7;

        for (int i = 1; i < power_max_time_steps; i++) {
            for (int j = 2; j < power_max_n_samples; j++) {

                timeSteps = pow(10, i);
                n_samples = pow(10, j);

                ext::shared_ptr<PricingEngine> mcengine1;
                mcengine1 = MakeMCEuropeanEngine_2<PseudoRandom>(bsmProcess)
                    .withSteps(timeSteps)
                    // .withAbsoluteTolerance(0.01)
                    .withSeed(mcSeed)
                    .withSamples(n_samples)
                    .isConstantBS(isConstantBS);
                europeanOption.setPricingEngine(mcengine1);

                auto startTime1 = std::chrono::steady_clock::now();

                Real NPV1 = europeanOption.NPV();

                std::cout << "time steps : " << timeSteps << std::endl;
                std::cout << "number of samples : " << n_samples << std::endl;

                auto endTime1 = std::chrono::steady_clock::now();

                double us1 = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1).count();

                Real errorEstimate1 = europeanOption.errorEstimate();

                std::cout << "Error estimation = " << errorEstimate1 << std::endl;
                std::cout << "NPV: " << NPV1 << std::endl;
                std::cout << "Running time: " << us1 / 1000000 << " s" << std::endl;

                std::cout << "===================================" << std::endl;


                ext::shared_ptr<PricingEngine> mcengine2;
                mcengine2 = MakeMCEuropeanEngine_2<PseudoRandom>(bsmProcess)
                    .withSteps(timeSteps)
                    // .withAbsoluteTolerance(0.01)
                    .withSeed(mcSeed)
                    .withSamples(n_samples);
                europeanOption.setPricingEngine(mcengine2);

                auto startTime2 = std::chrono::steady_clock::now();

                Real NPV2 = europeanOption.NPV();

                std::cout << "time steps : " << timeSteps << std::endl;
                std::cout << "number of samples : " << n_samples << std::endl;

                auto endTime2 = std::chrono::steady_clock::now();

                double us2 = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime2).count();

                Real errorEstimate2 = europeanOption.errorEstimate();

                std::cout << "Error estimation = " << errorEstimate2 << std::endl;
                std::cout << "NPV: " << NPV2 << std::endl;
                std::cout << "Running time: " << us2 / 1000000 << " s" << std::endl;
                std::cout << "===================================" << std::endl;

            }
        }

        return 0;


    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}

