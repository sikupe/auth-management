//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONCONTROLLER_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONCONTROLLER_H

#include <oatpp/web/server/api/ApiController.hpp>
#include "db/UserDb.h"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "service/PermissionService.h"
#include "dto/PermissionDto.h"
#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)

class PermissionController : public oatpp::web::server::api::ApiController {
    OATPP_COMPONENT(std::shared_ptr<PermissionService>, m_permissionService);
public:
    explicit PermissionController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT("POST", "/permissions", create,
             BODY_DTO(oatpp::Object<PermissionDto>, permission
             )) {
        return createDtoResponse(Status::CODE_200,
                                 m_permissionService->createPermission(permission));
    }

    ENDPOINT("PATCH", "/permissions/{id}", update,
             BODY_DTO(oatpp::Object<PermissionDto>, permission
             ),
             PATH(String, id
             )) {
        return createDtoResponse(Status::CODE_200,
                                 m_permissionService->updatePermission(id, permission));
    }

    ENDPOINT("UPDATE", "/permissions/{id}", del,
             PATH(String, id
             )) {
        m_permissionService->deletePermission(id);
        return createResponse(Status::CODE_200);
    }

    ENDPOINT("GET", "/permissions/{id}", get,
             PATH(String, id
             )) {
        return createDtoResponse(Status::CODE_200, m_permissionService->getPermission(id));
    }

    ENDPOINT("GET", "/permissions", list) {
        return createDtoResponse(Status::CODE_200, m_permissionService->listPermissions());
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONCONTROLLER_H
