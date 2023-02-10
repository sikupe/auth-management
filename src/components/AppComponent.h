//
// Created by simon on 28.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H
#define AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H

#include "dto/ConfigDto.h"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"
#include "service/PermissionProviderService.h"
#include "service/PermissionService.h"
#include "service/PermissionRequestService.h"
#include "service/connectors/KeyCloakConnector.h"

#include <cstdlib>
#include <string>

using namespace std;

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

    OATPP_CREATE_COMPONENT(shared_ptr<KeyCloakConnector>, keyCloakConnector)([] {
        string base = "127.0.0.1";
        unsigned short port = 8080;
        const auto baseEnv = ::getenv("KEYCLOAK_HOST");
        const auto portEnv = ::getenv("KEYCLOAK_PORT");

        if(baseEnv != nullptr) {
            base = baseEnv;
        }

        if (portEnv != nullptr) {
            port = stoi(portEnv);
        }

        return make_shared<KeyCloakConnector>(base, port);
    }());
};

#endif //AUTHORIZATION_MANAGEMENT_APPCOMPONENT_H
