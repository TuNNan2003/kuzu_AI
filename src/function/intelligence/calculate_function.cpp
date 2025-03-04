#include "function/Intelligence/functions/calculate_function.h"
#include "function/scalar_function.h"

using namespace kuzu::common;
namespace kuzu {
namespace function {
    void Calculate::operation(common::ku_string_t& input, common::ku_string_t& result,
    common::ValueVector& resultValueVector) {
    printf("calculate:operation:11\t input: %s\n", input.getAsString().c_str());
    const std::string& ai_req = "扮演一个计算器，对于给定的输入，首先判断是否是合法的,如果非法则直接返回'error',如果合法则进行计算，返回计算结果,注意仅返回error，仅返回最终的数字结果";
    std::string req = ai_req + " 输入: " + "根号3加根号2保留小数点后两位";
    printf("calculate:operation:12\t req: %s\n", req.c_str());
    aiRequester.request(req, result, resultValueVector);
}
} // namespace function
} // namespace kuzu
