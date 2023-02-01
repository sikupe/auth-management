//
// Created by simon on 31.01.23.
//

#ifndef AUTHORIZATION_MANAGEMENT_CONNECTOR_H
#define AUTHORIZATION_MANAGEMENT_CONNECTOR_H

#include "dto/PermissionRequest.h"
#include <string>
#include "dto/ConfigPair.h"
#include "dto/PermissionRequestResponse.h"

#include "oatpp/core/macro/component.hpp"

#include <oatpp/core/Types.hpp>
using namespace std;

class Connector {
public:
    virtual ~Connector() = default;

    virtual void synchronize(const Vector<Object<PermissionRequestResponse>> &permissionRequest) = 0;
    [[nodiscard]] string getValue(const Vector<Object<ConfigPairRequest>> &configPairs, const string &key) const;
};


#endif //AUTHORIZATION_MANAGEMENT_CONNECTOR_H
