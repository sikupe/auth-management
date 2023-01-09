//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionRequest : public oatpp::DTO {
    DTO_INIT(PermissionRequest, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, requestor, "requester");

    DTO_FIELD(String, request_date, "request_date");

    DTO_FIELD(String, invalidation_date, "invalidation_date");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONREQUEST_H
