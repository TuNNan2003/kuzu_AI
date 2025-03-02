#pragma once

#include "common/types/ku_string.h"
#include "common/vector/value_vector.h"
namespace kuzu {
namespace function {

struct Calculate {
    static inline void operation(common::ku_string_t& input, common::ku_string_t& result,
        common::ValueVector& resultValueVector) {
        printf("calculate:operation:11\t input: %s\n", input.getAsString().c_str());
        result.set("abcdefghijkl");
    }
};

} // namespace function
} // namespace kuzu 