//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTCONTROLLER_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTCONTROLLER_H


#include <oatpp/web/server/api/ApiController.hpp>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <memory>
#include "dto/PermissionRequest.h"
#include "service/PermissionRequestService.h"
#include "dto/PermissionRequestDto.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class PermissionRequestController : public oatpp::web::server::api::ApiController {
    OATPP_COMPONENT(std::shared_ptr<PermissionRequestService>, m_permissionService);
public:
    explicit PermissionRequestController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT("POST", "/permission-requests", create,
             BODY_DTO(oatpp::Object<PermissionRequestDto>, permissionRequest
             )) {
        return createDtoResponse(Status::CODE_200,
                                 m_permissionService->createPermissionRequest(permissionRequest));
    }

    ENDPOINT("PATCH", "/permission-requests/{id}", update,
             BODY_DTO(oatpp::Object<PermissionRequestDto>, permissionRequest
             ),
             PATH(String, id
             )) {
        return createDtoResponse(Status::CODE_200,
                                 m_permissionService->updatePermissionRequest(id, permissionRequest));
    }

    ENDPOINT("PATCH", "/permission-requests/{id}", del,
             PATH(String, id
             )) {
        m_permissionService->deletePermissionRequest(id);
        return createResponse(Status::CODE_200);
    }

    ENDPOINT("GET", "/permission-requests/{id}", get,
             PATH(String, id
             )) {
        return createDtoResponse(Status::CODE_200, m_permissionService->getPermissionRequest(id));
    }

    ENDPOINT("GET", "/permission-requests", list) {
        return createDtoResponse(Status::CODE_200, m_permissionService->listPermissionRequests());
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTCONTROLLER_H
