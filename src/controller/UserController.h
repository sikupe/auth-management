//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_USERCONTROLLER_H
#define AUTHORIZATION_MANAGEMENT_USERCONTROLLER_H

#include <oatpp/web/server/api/ApiController.hpp>
#include "db/UserDb.h"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "dto/UserDto.h"

#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)
#include "service/UserService.h"

class UserController : public oatpp::web::server::api::ApiController {
private:
    UserService m_userService;
public:
    explicit UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT("GET", "/users", getUser) {
        return createDtoResponse(Status::CODE_200, m_userService.getUsers());
    }

    ENDPOINT("POST", "/users", createUser, BODY_DTO(oatpp::Object<UserDto>, user)) {
        return createDtoResponse(Status::CODE_200, m_userService.createUser(user));
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //AUTHORIZATION_MANAGEMENT_USERCONTROLLER_H
