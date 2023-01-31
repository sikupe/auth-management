//
// Created by simon on 29.01.23.
//

#include <oatpp/web/protocol/http/Http.hpp>
#include "PermissionService.h"
#include "dto/PageDto.h"
#include "dto/PermissionResponse.h"

typedef oatpp::web::protocol::http::Status Status;

oatpp::Object<PermissionResponse>
PermissionService::createPermission(const oatpp::data::mapping::type::DTOWrapper<PermissionDto> &permissionDto) {
    const auto result = m_permissionDb->createPermission(permissionDto);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage())
    const auto ps = result->fetch<oatpp::Vector<oatpp::Object<Permission>>>();
    const auto p = ps[0];

    for (size_t i = 0; i < permissionDto->config->size(); i++) {
        const auto &c = permissionDto->config[i];
        m_configPairDb->insertConfigPairsForPermission(p->id, c);
    }

    const auto permissionProvider = m_permissionProviderService->getPermissionProvider(p->permission_provider_id, false);

    const auto pr = PermissionResponse::createShared();

    pr->id = p->id;
    pr->name = p->name;
    pr->description = p->description;
    pr->config = permissionDto->config;
    pr->permission_provider = permissionProvider;

    return pr;
}

oatpp::Object<PermissionResponse>
PermissionService::updatePermission(const oatpp::String &id, const oatpp::Object<PermissionDto> &permission) {
    auto result = this->m_permissionDb->updatePermission(id, permission);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage())
    const auto ps = result->fetch<oatpp::Vector<oatpp::Object<Permission>>>();
    const auto p = ps[0];

    m_configPairDb->deleteConfigPairsForPermission(p->id);

    for (size_t i = 0; i < permission->config->size(); i++) {
        const auto &c = permission->config[i];
        m_configPairDb->insertConfigPairsForPermission(p->id, c);
    }

    const auto permissionProvider = m_permissionProviderService->getPermissionProvider(p->permission_provider_id, false);

    const auto pr = PermissionResponse::createShared();

    pr->id = p->id;
    pr->name = p->name;
    pr->description = p->description;
    pr->config = permission->config;
    pr->permission_provider = permissionProvider;

    return pr;
}

void PermissionService::deletePermission(const oatpp::String &id) {
    this->m_permissionDb->deletePermission(id);
}

oatpp::Object<PermissionResponse> PermissionService::getPermission(const oatpp::String &id) {
    auto result = this->m_permissionDb->getPermission(id);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_404, result->getErrorMessage())
    const auto ps = result->fetch<oatpp::Vector<oatpp::Object<Permission>>>();
    const auto p = ps[0];

    const auto pr = PermissionResponse::createShared();

    const auto config_res = m_configPairDb->getConfigPairsForPermission(p->id);
    OATPP_ASSERT_HTTP(config_res->isSuccess(), Status::CODE_500, config_res->getErrorMessage())

    const auto configPairs = config_res->fetch<oatpp::Vector<oatpp::Object<ConfigPairRequest>>>();

    const auto permissionProvider = m_permissionProviderService->getPermissionProvider(p->permission_provider_id, false);

    pr->id = p->id;
    pr->name = p->name;
    pr->description = p->description;
    pr->permission_provider = permissionProvider;
    pr->config = configPairs;

    return pr;
}

oatpp::Object<PageDto<oatpp::Object<PermissionResponse>>> PermissionService::listPermissions() {
    int start = 0;
    int step_size = 100;
    bool has_more = true;
    auto pageDto = PageDto<oatpp::Object<PermissionResponse>>::createShared();
    pageDto->items = {};
    pageDto->size = 0U;
    do {
        auto res = m_permissionDb->listPermissions(start, step_size);
        OATPP_ASSERT_HTTP(res->isSuccess(), Status::CODE_500, res->getErrorMessage())

        const auto savedPermissions = res->fetch<oatpp::Vector<oatpp::Object<Permission>>>();

        if (savedPermissions->empty()) {
            has_more = false;
        }

        for (int i = 0; i < savedPermissions->size(); ++i) {
            const auto p = savedPermissions[i];
            const auto pr = PermissionResponse::createShared();

            pr->id = p->id;
            pr->name = p->name;
            pr->description = p->description;
            pageDto->items->push_back(pr);
        }

        for (size_t j = pageDto->size; j < savedPermissions->size(); j++) {
            const auto &permission = pageDto->items[j];


            const auto config_res = m_configPairDb->getConfigPairsForPermission(
                    permission->id);
            OATPP_ASSERT_HTTP(config_res->isSuccess(), Status::CODE_500, config_res->getErrorMessage())

            permission->config = config_res->fetch<oatpp::Vector<oatpp::Object<ConfigPairRequest>>>();

            const auto permission_provider_id = savedPermissions[j - pageDto->size]->permission_provider_id;
            if (permission_provider_id) {
                const auto permissionProvider = m_permissionProviderService->getPermissionProvider(
                        permission_provider_id, false);
                permission->permission_provider = permissionProvider;
            }
        }

        pageDto->size = pageDto->size + savedPermissions->size(); // += not overloaded for some reason

        start += step_size;
    } while (has_more);

    return pageDto;
}
