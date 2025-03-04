#pragma once

#include "common/types/ku_string.h"
#include "common/vector/value_vector.h"
#include <string>

namespace kuzu {
namespace function {

class ModelInfo {
public:
    ModelInfo() = default;
    ModelInfo(std::string name, std::string url, std::string key) 
        : modelName(std::move(name)), apiUrl(std::move(url)), modelAPIKey(std::move(key)) {}
    std::string GetModelName() const { return modelName; }
    std::string GetApiUrl() const { return apiUrl; }
    std::string GetModelAPIKey() const { return modelAPIKey; }
private:
    std::string modelName;
    std::string apiUrl;
    std::string modelAPIKey;
};

class AIRequester {
    public:
    static void request(std::string query, common::ku_string_t& result,common::ValueVector& resultValueVector);
    static void requestWithSpecificModel(const common::ku_string_t& query, common::ku_string_t& result, 
        const std::string& model);
    static std::string getModelInfoList();
    bool AddModel();
    private:
    static const std::vector<ModelInfo> modelInfoList;
};
} // namespace function
} // namespace kuzu