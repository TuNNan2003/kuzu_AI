#pragma once

#include "common/types/ku_string.h"
#include "common/vector/value_vector.h"
namespace kuzu {
namespace function {

struct Calculate {
    static void operation(common::ku_string_t& input, common::ku_string_t& result,
        common::ValueVector& resultValueVector);
};

} // namespace function
} // namespace kuzu 