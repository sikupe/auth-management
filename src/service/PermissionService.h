//
// Created by simon on 29.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONSERVICE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONSERVICE_H


#include <oatpp/orm/Connection.hpp>
#include <oatpp/core/provider/Provider.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

#include "oatpp/core/macro/component.hpp"

#include <oatpp/core/Types.hpp>
#include "dto/PermissionDto.h"
#include "db/PermissionDb.h"
#include "dto/PageDto.h"
#include "db/ConfigPairDb.h"
#include "dto/PermissionResponse.h"
#include "db/PermissionProviderDb.h"
#include "PermissionProviderService.h"

class PermissionService {
    OATPP_COMPONENT(std::shared_ptr<PermissionDb>, m_permissionDb);
    OATPP_COMPONENT(std::shared_ptr<PermissionProviderService>, m_permissionProviderService);
    OATPP_COMPONENT(std::shared_ptr<ConfigPairDb>, m_configPairDb);

public:
    oatpp::Object<PermissionResponse> createPermission(const oatpp::Object<PermissionDto> &permissionDto);

    oatpp::Object<PermissionResponse>
    updatePermission(const oatpp::String &string, const oatpp::Object<PermissionDto> &wrapper);

    void deletePermission(const oatpp::String &string);

    oatpp::Object<PermissionResponse> getPermission(const oatpp::String &string);

    oatpp::Object<PageDto<oatpp::Object<PermissionResponse>>> listPermissions();
};


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONSERVICE_H
