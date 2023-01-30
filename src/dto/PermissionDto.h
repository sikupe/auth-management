//
// Created by simon on 29.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONDTO_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONDTO_H


#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "ConfigPairRequest.h"


#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionDto : public oatpp::DTO {
    DTO_INIT(PermissionDto, DTO);

    DTO_FIELD(String, permission_provider_id, "permission_provider_id");

    DTO_FIELD(String, name, "name");

    DTO_FIELD(String, description, "description");

    DTO_FIELD(oatpp::Vector<oatpp::Object<ConfigPairRequest>>, config, "config");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONDTO_H
