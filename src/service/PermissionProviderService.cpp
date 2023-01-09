//
// Created by simon on 07.01.23.
//

#include "PermissionProviderService.h"

#include "oatpp/web/protocol/http/Http.hpp"

typedef oatpp::web::protocol::http::Status Status;

oatpp::Object<PermissionProviderResponse> PermissionProviderService::createPermissionProvider(
        const oatpp::Object<PermissionProviderRequest> &permissionProviderRequest) {

    const auto pp_result = m_permissionProviderDb->createPermissionProvider(permissionProviderRequest->toPermissionProvider());
    OATPP_ASSERT_HTTP(pp_result->isSuccess(), Status::CODE_500, pp_result->getErrorMessage())
    const auto pps = pp_result->fetch<oatpp::Vector<oatpp::Object<PermissionProvider>>>();
    const auto pp = pps[0];

    for (size_t i = 0; i < permissionProviderRequest->config->size(); i++) {
        const auto &c = permissionProviderRequest->config[i];
        m_configPairDb->insertConfigPairsForPermissionProvider(pp->id, c);
    }

    const auto ppr = PermissionProviderResponse::createShared();

    ppr->id = pp->id;
    ppr->type = pp->type;
    ppr->config = permissionProviderRequest->config;

    return ppr;
}
