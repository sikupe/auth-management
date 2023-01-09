//
// Created by simon on 07.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERSERVICE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERSERVICE_H

#include "memory"
#include "dto/PermissionProviderResponse.h"
#include "dto/PermissionProviderRequest.h"

#include <oatpp/orm/Connection.hpp>
#include <oatpp/core/provider/Provider.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

#include "oatpp/core/macro/component.hpp"

#include "db/ConfigPairDb.h"
#include "db/PermissionProviderDb.h"

using namespace std;

class PermissionProviderService {
private:
    OATPP_COMPONENT(std::shared_ptr<PermissionProviderDb>, m_permissionProviderDb);
    OATPP_COMPONENT(std::shared_ptr<ConfigPairDb>, m_configPairDb);

public:
    oatpp::Object<PermissionProviderResponse>
    createPermissionProvider(const oatpp::Object<PermissionProviderRequest> &permissionProviderRequest);
};


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDERSERVICE_H
