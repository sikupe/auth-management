//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_SYNCHRONIZATIONSERVICE_H
#define AUTHORIZATION_MANAGEMENT_SYNCHRONIZATIONSERVICE_H

#include "oatpp/core/macro/component.hpp"
#include "service/connectors/KeyCloakConnector.h"
#include "PermissionRequestService.h"

#include <oatpp/core/Types.hpp>
#include <oatpp/core/async/Coroutine.hpp>
#include <memory>

class SynchronizationService : public oatpp::async::Coroutine<SynchronizationService> {
    OATPP_COMPONENT(shared_ptr<KeyCloakConnector>, keyCloakConnector);
    OATPP_COMPONENT(shared_ptr<PermissionRequestService>, permissionRequestService);
public:
    Action act() override;
};


#endif //AUTHORIZATION_MANAGEMENT_SYNCHRONIZATIONSERVICE_H
