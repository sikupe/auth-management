//
// Created by simon on 07.01.23.
//

#include "PermissionProviderRequest.h"

oatpp::Object<PermissionProvider> PermissionProviderRequest::toPermissionProvider() {
    const auto permission_provider = PermissionProvider::createShared();
    permission_provider->type = this->type;
    return permission_provider;
}
