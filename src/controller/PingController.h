//
// Created by simon on 29.11.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_PINGCONTROLLER_H
#define AUTHORIZATION_MANAGEMENT_PINGCONTROLLER_H


#include <oatpp/web/server/api/ApiController.hpp>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)

class PingController : public oatpp::web::server::api::ApiController {
public:
    explicit PingController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT("GET", "/ping", root) {
        return createResponse(Status::CODE_200, "Pong");
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //AUTHORIZATION_MANAGEMENT_PINGCONTROLLER_H
