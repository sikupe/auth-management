//
// Created by simon on 30.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONRESPONSE_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONRESPONSE_H

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "ConfigPairRequest.h"
#include "PermissionProviderResponse.h"

#include OATPP_CODEGEN_BEGIN(DTO)

using namespace oatpp;

class PermissionResponse : public oatpp::DTO {
    DTO_INIT(PermissionResponse, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, name, "name");

    DTO_FIELD(String, description, "description");

    DTO_FIELD(oatpp::Vector<oatpp::Object<ConfigPairRequest>>, config, "config");

    DTO_FIELD(oatpp::Object<PermissionProviderResponse>, permission_provider, "permission_provider");
};

#include OATPP_CODEGEN_END(DTO)


#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONRESPONSE_H
