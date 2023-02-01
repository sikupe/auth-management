//
// Created by simon on 30.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSERVICE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSERVICE_H


#include <oatpp/core/Types.hpp>
#include "oatpp/core/macro/component.hpp"
#include "dto/PermissionRequest.h"
#include "dto/PermissionRequestDto.h"
#include "db/PermissionRequestDb.h"
#include "PermissionService.h"
#include "dto/PermissionRequestResponse.h"

class PermissionRequestService {
    OATPP_COMPONENT(std::shared_ptr<PermissionRequestDb>, m_permissionRequestDb);
    OATPP_COMPONENT(std::shared_ptr<PermissionService>, m_permissionService);
public:
    oatpp::Object<PermissionRequestResponse>
    createPermissionRequest(const oatpp::Object<PermissionRequestDto> &permissionRequest);

    oatpp::Object<PermissionRequestResponse>
    updatePermissionRequest(const oatpp::String &id, const oatpp::Object<PermissionRequestDto> &permissionRequest);

    oatpp::Object<PermissionRequestResponse> getPermissionRequest(const oatpp::String &id);

    oatpp::Object<PageDto<oatpp::Object<PermissionRequestResponse>>>
    listPermissionRequests(bool permissionProviderConfig);

    void deletePermissionRequest(const oatpp::String &id);
};


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUESTSERVICE_H
