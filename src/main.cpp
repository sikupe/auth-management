#include <oatpp/web/server/HttpConnectionHandler.hpp>

#include <oatpp/network/Server.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

#include "controller/PingController.h"

#include <memory>

using namespace std;

int main() {
    oatpp::base::Environment::init();

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    auto pingController = make_shared<PingController>();

    auto router = oatpp::web::server::HttpRouter::createShared();
    router->addController(pingController);

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
            {"0.0.0.0", 8000, oatpp::network::Address::IP_4});
    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    server.run();

    oatpp::base::Environment::destroy();

    return 0;
}
