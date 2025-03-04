#include "function/Intelligence/executor/ai_requester.h"
#include <vector>
#include <curl/curl.h>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

using namespace kuzu::common;

namespace kuzu {
namespace function {

const std::vector<ModelInfo> AIRequester::modelInfoList = {
    ModelInfo("deepseek-v3","https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions",
    "sk-2e38f082fb8f4be0aee3ba890f5475fa")
};

// 响应写入回调
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total = size * nmemb;
    output->append((char*)contents, total);
    return total;
}

void AIRequester::request(std::string query, ku_string_t& result, common::ValueVector& resultValueVector) {
    result.set("123456789012");
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::string errMsg = "curl_easy_init failed";
        result.set("error");
        return;
    }

    json reqBody = {
        {"model", modelInfoList[0].GetModelName()},
        {"messages", {
            {{"role", "user"}, {"content", query}}
        }},
        {"temperature", 0.7}
    };
    std::string jsonStr = reqBody.dump();

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + modelInfoList[0].GetModelAPIKey()).c_str());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, modelInfoList[0].GetApiUrl().c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonStr.length());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // 开启详细日志
    // curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer); // 获取错误详情
    printf("Request Body: %s\n", jsonStr.c_str());
    CURLcode res = curl_easy_perform(curl);
    printf("curl_easy_perform res: %d\n", res);
    if (res != CURLE_OK) {
        std::string errMsg = "curl_easy_perform failed";
        result.setLongString(errMsg.c_str(), errMsg.length());
        return;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    printf("response: %s\n", response.c_str());

    try {
        json responseJson = json::parse(response);
        
        // 验证响应结构
        if (!responseJson.contains("choices") || 
            !responseJson["choices"].is_array() ||
            responseJson["choices"].empty()) 
        {
            printf("Invalid response format\n");
            result.set("Invalid response format");
            return;
        }

        auto& firstChoice = responseJson["choices"][0];
        if (!firstChoice.contains("message") || 
            !firstChoice["message"].is_object()) 
        {
            printf("Missing message in response\n");
            result.set("Missing message in response");
            return;
        }

        auto& message = firstChoice["message"];
        if (!message.contains("content") || 
            !message["content"].is_string()) 
        {
            printf("Missing content in message\n");
            result.set("Missing content in message");
            return;
        }

        std::string content = message["content"].get<std::string>();
        if(content.length() <= ku_string_t::SHORT_STR_LENGTH) {
            result.set(content.c_str());
        } else {
            StringVector::reserveString(&resultValueVector, result, content.length());
            auto buffer = reinterpret_cast<char*>(result.overflowPtr);
            memcpy(buffer, content.c_str(), content.length());
            result.len = content.length();
            memcpy(result.prefix, buffer, result.len < ku_string_t::PREFIX_LENGTH ? result.len : ku_string_t::PREFIX_LENGTH);
        }

    } catch (const json::exception& e) {
        printf("JSON parse error: %s\n", e.what());
        result.set("JSON parse error: " + std::string(e.what()));
    } catch (...) {
        printf("Unknown response parse error\n");
        result.set("Unknown response parse error");
    }
}



} // namespace function
} // namespace kuzu 