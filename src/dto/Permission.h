//
// Created by simon on 02.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_PERMISSION_H
#define AUTHORIZATION_MANAGEMENT_PERMISSION_H


#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class Permission : public oatpp::DTO {
    DTO_INIT(Permission, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, permission_provider_id, "permission_provider_id");

    DTO_FIELD(String, name, "name");

    DTO_FIELD(String, description, "description");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_PERMISSION_H
