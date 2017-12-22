// Copyright 2017 <Célian Garcia>

#ifndef FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_RESPONSEBUILDER_HPP_
#define FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_RESPONSEBUILDER_HPP_

#include <string>
#include <json/json.hpp>
#include <firefly/core/utils/server_types_definitions.hpp>
#include <firefly/core/data/Operation.hpp>

namespace firefly {

class ResponseBuilder {
 public:
    static void build(std::string content, std::shared_ptr<HttpResponse> response);

    static void build(nlohmann::json raw_content, std::shared_ptr<HttpResponse> response);

    static void build(const char *raw_content, std::shared_ptr<HttpResponse> response);
};

}  // namespace firefly

#endif  // FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_RESPONSEBUILDER_HPP_
