//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_KEYCLOAKCLIENT_H
#define AUTHORIZATION_MANAGEMENT_KEYCLOAKCLIENT_H

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient) ///< Begin code-gen section

class KeyCloakClient : public oatpp::web::client::ApiClient {
API_CLIENT_INIT(KeyCloakClient);

    API_CALL("DELETE", "/admin/realms/{realm}/users/{userId}/groups/", listGroups, PATH(String, realm),
             PATH(String, userId),
             HEADER(String, token, "Authorization Bearer")
    );

    API_CALL("PUT", "/admin/realms/{realm}/users/{userId}/groups/{groupId}", addGroup, PATH(String, realm),
             PATH(String, userId),
             PATH(String, groupId),
             HEADER(String, token, "Authorization Bearer")
    );

    API_CALL("DELETE", "/admin/realms/{realm}/users/{userId}/groups/{groupId}", deleteGroup, PATH(String, realm),
             PATH(String, userId),
             PATH(String, groupId),
             HEADER(String, token, "Authorization Bearer")
    );

    API_CALL("POST", "/auth/realms/{realm}/protocol/openid-connect/token", login, PATH(String, realm),
             BODY_STRING(String, loginData)
    );
};

#include OATPP_CODEGEN_END(ApiClient) ///< End code-gen section

#endif //AUTHORIZATION_MANAGEMENT_KEYCLOAKCLIENT_H
