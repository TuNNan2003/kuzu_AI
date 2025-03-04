#pragma once

#include "common/types/ku_string.h"
#include "common/vector/value_vector.h"
#include "function/Intelligence/executor/ai_requester.h"
namespace kuzu {
namespace function {

struct Calculate {
    static void operation(common::ku_string_t& input, common::ku_string_t& result,
        common::ValueVector& resultValueVector);
    private:
    static AIRequester aiRequester;
};

} // namespace function
} // namespace kuzu 