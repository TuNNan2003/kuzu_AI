#include "function/Intelligence/functions/calculate_function.h"
#include "function/scalar_function.h"

using namespace kuzu::common;
namespace kuzu {
namespace function {
    void Calculate::operation(common::ku_string_t& input, common::ku_string_t& result,
    common::ValueVector& resultValueVector) {
    printf("calculate:operation:11\t input: %s\n", input.getAsString().c_str());
    result.set("abcdefghijk");
}
} // namespace function
} // namespace kuzu
