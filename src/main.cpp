#include <oatpp/web/server/HttpConnectionHandler.hpp>

#include <oatpp/network/Server.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

#include "controller/PingController.h"
#include "components/AppComponent.h"
#include "components/DatabaseComponent.h"
#include "controller/UserController.h"
#include "controller/PermissionController.h"
#include "controller/PermissionProviderController.h"
#include "components/ConfigComponent.h"
#include "controller/PermissionRequestController.h"
#include "service/SynchronizationService.h"

#include <memory>
#include <oatpp/core/async/Executor.hpp>

using namespace std;

int main() {
    oatpp::base::Environment::init();

    ConfigComponent configComponent;
    DatabaseComponent databaseComponent;
    AppComponent appComponent;

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

    auto pingController = make_shared<PingController>();
    auto userController = make_shared<UserController>();
    auto permissionProviderController = make_shared<PermissionProviderController>();
    auto permissionController = make_shared<PermissionController>();
    auto permissionRequestController = make_shared<PermissionRequestController>();

    auto router = oatpp::web::server::HttpRouter::createShared();
    router->addController(pingController);
    router->addController(userController);
    router->addController(permissionProviderController);
    router->addController(permissionController);
    router->addController(permissionRequestController);

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
            {"127.0.0.1", 8000, oatpp::network::Address::IP_4});
    oatpp::network::Server server(connectionProvider, connectionHandler);

    oatpp::async::Executor executor;

    executor.execute<SynchronizationService>();

    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    server.run();

    executor.waitTasksFinished();
    executor.stop();
    executor.join();

    oatpp::base::Environment::destroy();

    return 0;
}
