//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_TOKENDTO_H
#define AUTHORIZATION_MANAGEMENT_TOKENDTO_H


#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "ConfigPairRequest.h"
#include "PermissionProviderResponse.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class TokenDto : public oatpp::DTO {
    DTO_INIT(TokenDto, DTO);

    DTO_FIELD(String, access_token, "access_token");

    DTO_FIELD(UInt32, expires_in, "expires_in");

    DTO_FIELD(UInt32, refresh_expires_in, "refresh_expires_in");

    DTO_FIELD(String, refresh_token, "refresh_token");

    DTO_FIELD(String, token_type, "token_type");

    DTO_FIELD(UInt32, not_before_policy, "not-before-policy");

    DTO_FIELD(String, session_state, "session_state");

    DTO_FIELD(String, scope, "scope");
};

#include OATPP_CODEGEN_END(DTO)

#endif //AUTHORIZATION_MANAGEMENT_TOKENDTO_H
