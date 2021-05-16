#include "MatlabMexFunction.h"

class MexFunction : public MatlabMexFunction
{
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        checkArguments(outputs, inputs);
        double multiplier = inputs[0][0];
        matlab::data::TypedArray<double> in = std::move(inputs[1]);
        arrayProduct(in, multiplier);
        outputs[0] = std::move(in);
    }

    void arrayProduct(matlab::data::TypedArray<double>& inMatrix, double multiplier)
    {
        for (auto& elem : inMatrix)
        {
            elem *= multiplier;
        }
    }

    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        if (inputs.size() != 2)
        {
            eprintf("Two inputs required");
        }

        if (inputs[0].getNumberOfElements() != 1)
        {
            error("Input multiplier must be a scalar");
        }

        if (inputs[0].getType() != matlab::data::ArrayType::DOUBLE ||
             inputs[0].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE)
        {
            error("Input multiplier must be a noncomplex scalar double");
        }

        if (inputs[1].getType() != matlab::data::ArrayType::DOUBLE ||
             inputs[1].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE)
        {
            error("Input matrix must be type double");
        }

        if (inputs[1].getDimensions().size() != 2)
        {
            error("Input must be m-by-n dimension");
        }
    }
};
