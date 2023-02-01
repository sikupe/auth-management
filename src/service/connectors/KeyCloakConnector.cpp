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
                    {"", 80, oatpp::network::Address::IP_4});

            /* create HTTP request executor */
            auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);

            /* create JSON object mapper */
            auto keyCloakClient = KeyCloakClient::createShared(requestExecutor, mapper);

            const auto realm = this->getValue(permissionRequest->permission->config, "realm");
            const auto username = this->getValue(permissionRequest->permission->permission_provider->config,
                                                 "username");
            const auto password = this->getValue(permissionRequest->permission->permission_provider->config,
                                                 "password");
            const string userId = permissionRequest->requestor;
            const auto groupId = this->getValue(permissionRequest->permission->config, "groupId");
            const auto token = this->login(username, password, realm, keyCloakClient);

            if (permissionRequest->status == PermissionRequestStatus::Granted &&
                permissionRequest->invalidation_date < now) {
                keyCloakClient->addGroup(realm, userId, groupId, token->access_token);
            } else {
                keyCloakClient->deleteGroup(realm, userId, groupId, token->access_token);
            }
        }
    }
}

Object<TokenDto> KeyCloakConnector::login(const string &username, const string &password, const string &realm,
                                          const shared_ptr<KeyCloakClient>& keyCloakClient) {
    auto mapper = make_shared<parser::json::mapping::ObjectMapper>();

    ostringstream ss;
    ss << "grant_type=password" << endl;
    ss << "client_id=admin-cli" << endl;
    ss << "username=" << username << endl;
    ss << "password=" << password << endl;

    return keyCloakClient->login(realm, ss.str())->readBodyToDto<Object<TokenDto>>(mapper);
}

