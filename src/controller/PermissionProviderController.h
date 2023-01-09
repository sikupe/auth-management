//
// Created by simon on 05.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERCONTROLLER_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERCONTROLLER_H

#include <oatpp/web/server/api/ApiController.hpp>
#include "db/UserDb.h"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "dto/PermissionProvider.h"
#include "service/PermissionProviderService.h"

#include <memory>

#include OATPP_CODEGEN_BEGIN(ApiController)
#include "service/UserService.h"

class PermissionProviderController : public oatpp::web::server::api::ApiController {
private:
    PermissionProviderService m_permissionProviderService;
public:
    explicit PermissionProviderController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper) {}

    ENDPOINT("POST", "/permission-providers", root, BODY_DTO(oatpp::Object<PermissionProviderRequest>, permission_provider)) {

        return createDtoResponse(Status::CODE_200, m_permissionProviderService.createPermissionProvider(permission_provider));
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERCONTROLLER_H