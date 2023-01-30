cmake_minimum_required(VERSION 3.23)
project(authorization_management)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC src/**)
file(GLOB_RECURSE TEST test/**)
file(GLOB MAIN src/main.cpp)
list(APPEND TEST ${SRC})
list(REMOVE_ITEM TEST ${MAIN})

add_library(auth-lib ${SRC} src/controller/UserController.h src/service/UserService.cpp src/service/UserService.h src/dto/ConfigDto.h src/components/AppComponent.h src/dto/PageDto.h src/dto/PermissionProvider.cpp src/dto/PermissionProvider.h src/dto/ConfigPair.cpp src/dto/ConfigPair.h src/dto/PermissionProviderType.cpp src/dto/PermissionProviderType.h src/dto/Permission.cpp src/dto/Permission.h src/dto/PermissionRequest.cpp src/dto/PermissionRequest.h src/controller/PermissionController.h src/controller/PermissionProviderController.h src/controller/PermissionRequestController.h src/db/PermissionDb.h src/db/PermissionProviderDb.h src/db/ConfigPairDb.h src/db/PermissionRequestDb.h src/service/PermissionProviderService.cpp src/service/PermissionProviderService.h src/dto/PermissionProviderRequest.cpp src/dto/PermissionProviderRequest.h src/dto/ConfigPairRequest.cpp src/dto/ConfigPairRequest.h src/service/PermissionService.cpp src/service/PermissionService.h src/dto/PermissionDto.cpp src/dto/PermissionDto.h src/dto/PermissionResponse.cpp src/dto/PermissionResponse.h src/components/ConfigComponent.h)

## include directories

target_include_directories(auth-lib PUBLIC src)


## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)
#find_package(oatpp-swagger  1.3.0 REQUIRED)
#find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(auth-lib
        # Oat++
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-postgresql
        #        PUBLIC oatpp::oatpp-swagger
        #        PUBLIC oatpp::oatpp-sqlite
        )

# If CMake can't find SQLite3:
#
# 1. Make sure that you've built oatpp-sqlite with -DOATPP_SQLITE_AMALGAMATION=ON flag
# 2. If you are not willing to use SQLite amalgamation then uncomment the following lines:
#
#find_package(SQLite3 REQUIRED)
#
#target_link_libraries(auth-lib
#        PUBLIC SQLite::SQLite3
#)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(auth-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif ()

## add executables

add_executable(main ${MAIN})
target_link_libraries(main auth-lib)

#add_executable(crud-test ${TEST})
#target_link_libraries(crud-test auth-lib)
#
#enable_testing()
#add_test(project-tests crud-test)


