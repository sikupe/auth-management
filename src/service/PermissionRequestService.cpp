//
// Created by simon on 30.01.23.
//

#include <oatpp/web/protocol/http/Http.hpp>
#include "PermissionRequestService.h"
#include "dto/PermissionRequestResponse.h"

#include <ctime>

typedef oatpp::web::protocol::http::Status Status;


oatpp::Object<PermissionRequestResponse>
PermissionRequestService::createPermissionRequest(const oatpp::Object<PermissionRequestDto> &permissionRequest) {
    ::time_t requestedTime;
    time(&requestedTime);

    const auto result = m_permissionRequestDb->createPermissionRequest(permissionRequest, requestedTime);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage())
    const auto prs = result->fetch<oatpp::Vector<oatpp::Object<PermissionRequest>>>();
    const auto pr = prs[0];

    const auto prr = PermissionRequestResponse::createShared();

    prr->id = pr->id;
    prr->request_date = pr->request_date;
    prr->invalidation_date = pr->invalidation_date;
    prr->requestor = pr->requestor;
    prr->permission = m_permissionService->getPermission(pr->permission_id);
    prr->status = pr->status;

    return prr;
}

oatpp::Object<PermissionRequestResponse> PermissionRequestService::updatePermissionRequest(const String &id,
                                                                                           const Object<PermissionRequestDto> &permissionRequest) {
    const auto result = m_permissionRequestDb->updatePermissionRequest(id, permissionRequest);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage())
    const auto prs = result->fetch<oatpp::Vector<oatpp::Object<PermissionRequest>>>();
    const auto pr = prs[0];


    const auto prr = PermissionRequestResponse::createShared();

    prr->id = pr->id;
    prr->request_date = pr->request_date;
    prr->invalidation_date = pr->invalidation_date;
    prr->requestor = pr->requestor;
    prr->permission = m_permissionService->getPermission(pr->permission_id);
    prr->status = pr->status;

    return prr;
}

void PermissionRequestService::deletePermissionRequest(const String &id) {
    const auto result = m_permissionRequestDb->deletePermissionRequest(id);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_404, result->getErrorMessage())
}

oatpp::Object<PermissionRequestResponse> PermissionRequestService::getPermissionRequest(const String &id) {
    const auto result = m_permissionRequestDb->getPermissionRequest(id);
    OATPP_ASSERT_HTTP(result->isSuccess(), Status::CODE_500, result->getErrorMessage())
    const auto prs = result->fetch<oatpp::Vector<oatpp::Object<PermissionRequest>>>();
    const auto pr = prs[0];


    const auto prr = PermissionRequestResponse::createShared();

    prr->id = pr->id;
    prr->request_date = pr->request_date;
    prr->invalidation_date = pr->invalidation_date;
    prr->requestor = pr->requestor;
    prr->permission = m_permissionService->getPermission(pr->permission_id);
    prr->status = pr->status;

    return prr;
}

oatpp::Object<PageDto<oatpp::Object<PermissionRequestResponse>>> PermissionRequestService::listPermissionRequests() {
    int start = 0;
    int step_size = 100;
    bool has_more = true;
    auto pageDto = PageDto<oatpp::Object<PermissionRequestResponse>>::createShared();
    pageDto->items = {};
    pageDto->size = 0U;
    do {
        auto res = m_permissionRequestDb->listPermissionRequest(start, step_size);
        OATPP_ASSERT_HTTP(res->isSuccess(), Status::CODE_500, res->getErrorMessage())

        const auto savedPermissionRequests = res->fetch<oatpp::Vector<oatpp::Object<PermissionRequest>>>();

        if (savedPermissionRequests->empty()) {
            has_more = false;
        }

        for (int i = 0; i < savedPermissionRequests->size(); ++i) {
            const auto pr = savedPermissionRequests[i];
            const auto prr = PermissionRequestResponse::createShared();

            prr->id = pr->id;
            prr->request_date = pr->request_date;
            prr->invalidation_date = pr->invalidation_date;
            prr->requestor = pr->requestor;
            prr->permission = m_permissionService->getPermission(pr->permission_id);
            prr->status = pr->status;
        }

        pageDto->size = pageDto->size + savedPermissionRequests->size(); // += not overloaded for some reason

        start += step_size;
    } while (has_more);

    return pageDto;
}
