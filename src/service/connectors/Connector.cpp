//
// Created by simon on 31.01.23.
//

#include "Connector.h"

string Connector::getValue(const Vector<Object<ConfigPairRequest>> &configPairs, const string &key) const {
    for (size_t i = 0; i < configPairs->size(); i++) {
        const auto &c = configPairs[i];
        if (c->key == key) {
            return c->value;
        }
    }
    return "";
}
