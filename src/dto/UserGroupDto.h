//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_USERGROUPDTO_H
#define AUTHORIZATION_MANAGEMENT_USERGROUPDTO_H


#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class UserGroupDto : public oatpp::DTO {
    DTO_INIT(UserGroupDto, DTO);

    DTO_FIELD(String, id, "id");

    DTO_FIELD(String, name, "name");

    DTO_FIELD(String, path, "path");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_USERGROUPDTO_H
