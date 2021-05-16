#ifndef MATLABMEXFUNCTION_H
#define MATLABMEXFUNCTION_H

#include "mex.hpp"
#include "mexAdapter.hpp"

#define printf(...) MatlabMexFunction::disp(string_format(__VA_ARGS__))
#define eprintf(...) MatlabMexFunction::error(string_format(__VA_ARGS__))

template <typename... Args>
std::string string_format(const std::string& format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

class MatlabMexFunction : public matlab::mex::Function
{
protected:
    matlab::data::ArrayFactory factory;
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

public:
    //    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs);
    //    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs);
    void disp(const std::string& text)
    {
        matlabPtr->feval(u"disp", 0, std::vector<matlab::data::Array>({factory.createScalar(text)}));
    }
    void error(const std::string& text)
    {
        matlabPtr->feval(u"error", 0, std::vector<matlab::data::Array>({factory.createScalar(text)}));
    }
    void warning(const std::string& text)
    {
        matlabPtr->feval(u"warning", 0, std::vector<matlab::data::Array>({factory.createScalar(text)}));
    }
};

#endif // MATLABMEXFUNCTION_H
