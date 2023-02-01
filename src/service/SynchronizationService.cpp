//
// Created by simon on 31.01.23.
//

#include "SynchronizationService.h"
#include <chrono>

oatpp::async::Action SynchronizationService::act() {
    const auto permissionRequestsPageDto = permissionRequestService->listPermissionRequests(true);
    const auto permissionRequests = permissionRequestsPageDto->items;
    keyCloakConnector->synchronize(permissionRequests);
    return waitRepeat(std::chrono::seconds(30));
}
