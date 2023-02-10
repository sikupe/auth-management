//
// Created by simon on 31.01.23.
//

#include <oatpp/network/Address.hpp>
#include <oatpp/network/tcp/client/ConnectionProvider.hpp>
#include <oatpp/web/client/HttpRequestExecutor.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include "KeyCloakConnector.h"
#include "sstream"
#include "dto/PermissionRequestResponse.h"
#include "dto/TokenDto.h"

void KeyCloakConnector::synchronize(const Vector<Object<PermissionRequestResponse>> &permissionRequests) {
    auto mapper = make_shared<parser::json::mapping::ObjectMapper>();
    for (size_t i = 0; i < permissionRequests->size(); ++i) {
        const auto &permissionRequest = permissionRequests[i];

        time_t now;
        time(&now);

        if (permissionRequest->permission->permission_provider->type == PermissionProviderType::KeyCloak) {

            /* create connection provider */
            auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared(
                    {base, port, oatpp::network::Address::IP_4});

            /* create HTTP request executor */
            auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);

            /* create JSON object mapper */
            auto keyCloakClient = KeyCloakClient::createShared(requestExecutor, mapper);

            const auto realm = this->getValue(permissionRequest->permission->permission_provider->config, "realm");
            const auto username = this->getValue(permissionRequest->permission->permission_provider->config,
                                                 "username");
            const auto password = this->getValue(permissionRequest->permission->permission_provider->config,
                                                 "password");
            const string userId = permissionRequest->requestor;
            const auto groupId = this->getValue(permissionRequest->permission->config, "groupId");
            const auto token = this->login(username, password, realm, keyCloakClient);
            const auto bearerToken = "Bearer " + token->access_token;

            if (permissionRequest->status == PermissionRequestStatus::Granted &&
                permissionRequest->invalidation_date < now) {
                keyCloakClient->addGroup(realm, userId, groupId, bearerToken);
            } else {
                keyCloakClient->deleteGroup(realm, userId, groupId, bearerToken);
            }
        }
    }
}

Object<TokenDto> KeyCloakConnector::login(const string &username, const string &password, const string &realm,
                                          const shared_ptr<KeyCloakClient>& keyCloakClient) {
    auto mapper = make_shared<parser::json::mapping::ObjectMapper>();

    ostringstream ss;
    ss << "grant_type=password" << "&";
    ss << "client_id=admin-cli" << "&";
    ss << "username=" << username << "&";
    ss << "password=" << password;

    const auto response = keyCloakClient->login(realm, ss.str(), "application/x-www-form-urlencoded");
    const auto result = response->readBodyToDto<Object<TokenDto>>(mapper);
    return result;
}

