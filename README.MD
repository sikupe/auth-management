# Authorization Management

## Building

### Building locally
In order to build the project the following packages must be installed (Ubuntu):

- `postgresql-server-dev-14`

Furthermore, these dependencies must be build and installed using cmake and make:

- [Oat++](https://github.com/oatpp/oatpp)
- [Oat++ Postgresql](https://github.com/oatpp/oatpp-postgresql)

Follow the instructions provided there.

Afterwards can build it locally with:
```
mkdir build
cd build
cmake ..
make
```

### Using Dockerfile
You can also build a Dockerfile which can be used:
```docker build -t authmanagement .```

### Using docker compose
You can also start a complete setup with:
```docker compose up -d --build```


## Running the Service
The service exposes an REST API (currently without authentication or authorization), which can be used to request authorizations, which are synced into KeyCloak

### Not in docker
You first need to start the database and Keycloak:
```
docker compose -f docker-compose-local-db.yml up -d
docker compose -f docker-compose-keycloak.yml up -d
```

Afterwards you need to set the environment variable: ```DATABASE_CONNECTION=postgresql://test_user:test_pw@localhost:5432/test_db```

Afterwards you can start the binary or debug the application locally.

### Using docker
You can also start a complete setup using:
```docker compose -f docker-compose.yml up -d --build```

### Using setup_and_test.py
The `setup_and_test.py` script is setting up everything for you and also runs this scenario:
1. Create a group in KeyCloak
2. Create a user in the Auth Management
3. Create a PermissionProvider (reflecting the realm in KeyCloak) in the Auth Management
4. Create a Permission (reflecting the group in KeyCloak) in the Auth Management
5. Create a Permission Request on behalf of the user in the Auth Management
6. Granting the Permission Request
7. Checking if the user is synced into the group
8. Denying the Permission Request
9. Checking if the user is removed from the group

## Inspiration and code source

At the beginning I used [these examples](https://github.com/oatpp/example-postgresql) in order to get started with
Oat++. There might be some code snippets remaining from that time.