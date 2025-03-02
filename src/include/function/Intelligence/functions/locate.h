#pragma once

#include "common/types/ku_string.h"
#include "function/Intelligence/intelligence_function.h"
namespace kuzu {
namespace function {

struct LocationDetection {
    static inline void operation(common::ku_string_t& input, common::ku_string_t& result,
        common::ValueVector& resultValueVector) {
        printf("locate:operation:11\t input: %s\n", input.getAsString().c_str());
    }
};

} // namespace function
} // namespace kuzu