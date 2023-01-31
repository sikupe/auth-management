//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H
#define AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H

#include "dto/ConfigDto.h"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"
#include "service/PermissionProviderService.h"
#include "service/PermissionService.h"
#include "service/PermissionRequestService.h"

#include <cstdlib>

class AppComponent {
public:
    OATPP_CREATE_COMPONENT(shared_ptr<PermissionProviderService>, permissionProviderService)([] {
        return make_shared<PermissionProviderService>();
    }());

    OATPP_CREATE_COMPONENT(shared_ptr<PermissionService>, permissionService)([] {
        return make_shared<PermissionService>();
    }());

    OATPP_CREATE_COMPONENT(shared_ptr<PermissionRequestService>, permissionRequestService)([] {
        return make_shared<PermissionRequestService>();
    }());
};

#endif //AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H
