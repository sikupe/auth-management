//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDER_H
#define AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDER_H


#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "PermissionProviderType.h"


#include OATPP_CODEGEN_BEGIN(DTO)

class PermissionProvider : public oatpp::DTO {
    DTO_INIT(PermissionProvider, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(Enum<PermissionProviderType>::AsString, type, "type");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSIONPROVIDER_H
