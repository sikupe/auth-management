//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_KEYCLOAKCONNECTOR_H
#define AUTHORIZATION_MANAGEMENT_KEYCLOAKCONNECTOR_H

#include "Connector.h"
#include "KeyCloakClient.h"
#include "dto/PermissionRequestResponse.h"
#include "dto/TokenDto.h"
#include <string>
#include <memory>
#include <optional>
#include <utility>

using namespace std;

class KeyCloakConnector : public Connector {
    string base;
    unsigned short port;
    Object<TokenDto> login(const string &username, const string &password, const string &realm,
                           const shared_ptr<KeyCloakClient> &keyCloakClient);

public:
    explicit KeyCloakConnector(string base, unsigned short port) : Connector(), base(std::move(base)), port(port) {}

    void synchronize(const Vector<Object<PermissionRequestResponse>> &permissionRequests) override;
};


#endif //AUTHORIZATION_MANAGEMENT_KEYCLOAKCONNECTOR_H
