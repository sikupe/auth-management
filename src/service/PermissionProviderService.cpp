//
// Created by simon on 07.01.23.
//

#include "PermissionProviderService.h"

#include "oatpp/web/protocol/http/Http.hpp"

typedef oatpp::web::protocol::http::Status Status;

oatpp::Object<PermissionProviderResponse> PermissionProviderService::createPermissionProvider(
        const oatpp::Object<PermissionProviderRequest> &permissionProviderRequest) {

    const auto pp_result = m_permissionProviderDb->createPermissionProvider(
            permissionProviderRequest->toPermissionProvider());
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

oatpp::Object<PageDto<oatpp::Object<PermissionProviderResponse>>> PermissionProviderService::listPermissionProviders() {
    int start = 0;
    int step_size = 100;
    bool has_more = true;
    auto pageDto = PageDto<oatpp::Object<PermissionProviderResponse>>::createShared();
    pageDto->items = {};
    pageDto->size = 0U;
    do {
        auto res = m_permissionProviderDb->listPermissionProvider(start, step_size);
        OATPP_ASSERT_HTTP(res->isSuccess(), Status::CODE_500, res->getErrorMessage())

        const auto pps = res->fetch<oatpp::Vector<oatpp::Object<PermissionProviderResponse>>>();

        if (pps->empty()) {
            has_more = false;
        }

        for (size_t j = 0; j < pps->size(); j++) {
            const auto &permissionProviderRequest = pps[j];

            const auto config_res = m_configPairDb->getConfigPairsForPermissionProvider(
                    permissionProviderRequest->id);
            OATPP_ASSERT_HTTP(config_res->isSuccess(), Status::CODE_500, config_res->getErrorMessage())

            permissionProviderRequest->config = config_res->fetch<oatpp::Vector<oatpp::Object<ConfigPairRequest>>>();
        }

        pageDto->items->reserve(pageDto->items->size() + pps->size());
        pageDto->items->insert(pageDto->items->begin(), pps->begin(), pps->end());

        pageDto->size = pageDto->size + pps->size(); // += not overloaded for some reason

        start += step_size;
    } while (has_more);

    return pageDto;
}

const oatpp::Void &
PermissionProviderService::deletePermissionProvider(const oatpp::String &id) {
    this->m_permissionProviderDb->deletePermissionProvider(id);
}

oatpp::Object<PermissionProviderResponse> PermissionProviderService::updatePermissionProvider(const oatpp::String &id,
                                                                                              const oatpp::Object<PermissionProviderRequest> &permission_provider) {
    auto pp_result = this->m_permissionProviderDb->updatePermissionProvider(id, permission_provider);
    OATPP_ASSERT_HTTP(pp_result->isSuccess(), Status::CODE_500, pp_result->getErrorMessage())
    const auto pps = pp_result->fetch<oatpp::Vector<oatpp::Object<PermissionProvider>>>();
    const auto pp = pps[0];

    m_configPairDb->deleteConfigPairsForPermissionProvider(pp->id);

    for (size_t i = 0; i < permission_provider->config->size(); i++) {
        const auto &c = permission_provider->config[i];
        m_configPairDb->insertConfigPairsForPermissionProvider(pp->id, c);
    }

    const auto ppr = PermissionProviderResponse::createShared();

    ppr->id = pp->id;
    ppr->type = pp->type;
    ppr->config = permission_provider->config;

    return ppr;
}

oatpp::Object<PermissionProviderResponse> PermissionProviderService::getPermissionProvider(const oatpp::String &id, bool with_config) {
    auto pp_result = this->m_permissionProviderDb->getPermissionProvider(id);
    OATPP_ASSERT_HTTP(pp_result->isSuccess(), Status::CODE_404, pp_result->getErrorMessage())
    const auto pps = pp_result->fetch<oatpp::Vector<oatpp::Object<PermissionProvider>>>();
    const auto pp = pps[0];


    const auto config_res = m_configPairDb->getConfigPairsForPermissionProvider(
            pp->id);
    OATPP_ASSERT_HTTP(config_res->isSuccess(), Status::CODE_500, config_res->getErrorMessage())


    const auto ppr = PermissionProviderResponse::createShared();

    ppr->id = pp->id;
    ppr->type = pp->type;

    if (with_config) {
        const auto configPairs = config_res->fetch<oatpp::Vector<oatpp::Object<ConfigPairRequest>>>();
        ppr->config = configPairs;
    }

    return ppr;
}
