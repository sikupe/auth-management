//
// Created by simon on 09.12.22.
//

#ifndef AUTHORIZATION_MANAGEMENT_USERDTO_H
#define AUTHORIZATION_MANAGEMENT_USERDTO_H

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::DTO {
    DTO_INIT(UserDto, DTO)

    DTO_FIELD(String, id);

    DTO_FIELD(String, username, "username");

    DTO_FIELD(String, email, "email");

    DTO_FIELD(Boolean, is_admin, "is_admin");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_USERDTO_H
