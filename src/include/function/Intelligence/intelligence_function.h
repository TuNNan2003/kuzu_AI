#pragma once

#include "function/scalar_function.h"
#include "function/Intelligence/functions/locate.h"
#include "function/Intelligence/functions/calculate_function.h"
namespace kuzu {
namespace function {

struct VectorIntelligenceFunction {
    template<class OPERATION>
    static inline function_set getUnaryIntFunction(std::string funcName) {
        function_set functionSet;
        functionSet.emplace_back(make_unique<ScalarFunction>(funcName,
            std::vector<common::LogicalTypeID>{common::LogicalTypeID::INT64},
            common::LogicalTypeID::INT64,
            ScalarFunction::UnaryExecFunction<int64_t, int64_t, OPERATION>));
        return functionSet;
    }

    template<class OPERATION>
    static inline function_set getUnaryStrFunction(std::string funcName) {
        function_set functionSet;
        functionSet.emplace_back(make_unique<ScalarFunction>(funcName,
            std::vector<common::LogicalTypeID>{common::LogicalTypeID::STRING},
            common::LogicalTypeID::STRING,
            ScalarFunction::UnaryStringExecFunction<common::ku_string_t, common::ku_string_t, OPERATION>));
        return functionSet;
    }

    template<class OPERATION>
    static inline function_set getUnaryStrIntFunction(std::string funcName){
        function_set functionSet;
        functionSet.emplace_back(make_unique<ScalarFunction>(funcName,
        std::vector<common::LogicalTypeID>{common::LogicalTypeID::STRING},
        common::LogicalTypeID::INT64,
        ScalarFunction::UnaryExecFunction<common::ku_string_t, int64_t, OPERATION>));
        return functionSet;
    }
};


struct LocationDetectionFunction : public VectorIntelligenceFunction {
    static constexpr const char* name = "LOCATE";

    static inline function_set getFunctionSet() {
        return getUnaryStrFunction<LocationDetection>(name);
    }
};

struct CalculateFunction : public VectorIntelligenceFunction {
    static constexpr const char* name = "CALCULATE";

    static inline function_set getFunctionSet() {
        return getUnaryStrFunction<Calculate>(name);
    }
};

} // namespace function
} // namespace kuzu