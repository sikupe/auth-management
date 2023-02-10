import time
from time import sleep

import requests
import base64
import json
import os


def start_docker():
    os.system("docker compose -f docker-compose.yml down")
    os.system("docker compose -f docker-compose-keycloak.yml down")
    os.system("docker compose -f docker-compose-local-db.yml down")

    os.system("docker compose -f docker-compose-keycloak.yml up -d")
    os.system("docker compose -f docker-compose.yml up -d --build")


def wait_for_keycloak_startup(host: str):
    while True:
        try:
            response = requests.get(f'http://{host}')
            if response.ok:
                break
            sleep(1)
        except:
            pass
    sleep(5)


def login(host: str, username: str, password: str) -> str:
    response = requests.post(f'http://{host}/realms/master/protocol/openid-connect/token', data={
        'grant_type': 'password',
        'client_id': 'admin-cli',
        'username': username,
        'password': password
    })
    return response.json()['access_token']


def create_group(host: str, token: str, name: str, path: str) -> str:
    response = requests.post(f'http://{host}/admin/realms/master/groups', json={
        "name": name,
        "path": path
    }, headers={
        'Authorization': f'Bearer {token}'
    })

    response.raise_for_status()

    response = requests.get(f'http://{host}/admin/realms/master/groups', headers={
        'Authorization': f'Bearer {token}'
    })

    response.raise_for_status()

    groups = response.json()
    for group in groups:
        if group['name'] == name:
            return group['id']


def create_permission_provider(host: str, username: str, password: str) -> str:
    response = requests.post(f'http://{host}/permission-providers', json={
        "type": "KeyCloak",
        "config": [
            {
                "key": "realm",
                "value": "master"
            },
            {
                "key": "username",
                "value": username
            },
            {
                "key": "password",
                "value": password
            },
        ]
    })

    response.raise_for_status()

    return response.json()['id']


def create_permission(host: str, name: str, description: str, permission_provider_id: str, group_id: str) -> str:
    response = requests.post(f'http://{host}/permissions', json={
        "name": name,
        "description": description,
        "permission_provider_id": permission_provider_id,
        "config": [
            {
                "key": "groupId",
                "value": group_id
            }
        ]
    })

    response.raise_for_status()

    return response.json()['id']


def create_user(host: str, user_id: str, username: str, email: str, is_admin: bool):
    response = requests.post(f'http://{host}/users', json={
        "id": user_id,
        "username": username,
        "email": email,
        "is_admin": is_admin
    })

    response.raise_for_status()


def create_permission_request(host: str, user_id: str, invalidation_date: int, permission_id: str) -> str:
    response = requests.post(f'http://{host}/permission-requests', json={
        "requester": user_id,
        "invalidation_date": invalidation_date,
        "permission_id": permission_id
    })

    response.raise_for_status()

    return response.json()['id']


def approve_permission_request(host: str, permission_request_id: str):
    response = requests.get(f'http://{host}/permission-requests/{permission_request_id}')

    response.raise_for_status()

    data = response.json()
    data['status'] = 'Granted'
    data['permission_id'] = data['permission']['id']
    del data['permission']

    response = requests.patch(f'http://{host}/permission-requests/{data["id"]}', json=data)

    response.raise_for_status()


def get_user_id(token: str) -> str:
    payload = token[token.find('.') + 1:token.rfind('.')] + '=='
    decoded = base64.b64decode(payload).decode('utf8')
    payloadDecoded = json.loads(decoded)
    return payloadDecoded['sub']


def check_for_sync(host: str, user_id: str, group_id: str):
    response = requests.get(f'http://{host}/admin/realms/master/users/{user_id}/groups')

    result = response.json()
    for group in result:
        if group['id'] == group_id:
            return

    raise Exception('User not provisioned into group')


def main():
    keycloak_host = 'localhost:8080'
    auth_mgr_host = 'localhost:8000'
    keycloak_user = 'admin'
    keycloak_pw = 'admin123'
    permission_name = 'KeycloakGroupPermission'
    invalidation_date = 1696159871

    start_docker()

    print('Wait for startup')
    wait_for_keycloak_startup(keycloak_host)
    print('Waited for startup')

    token = login(keycloak_host, keycloak_user, keycloak_pw)

    user_id = get_user_id(token)

    group_id = create_group(keycloak_host, token, 'my-test-group', '/my-test-group')

    create_user(auth_mgr_host, user_id, "johndoe", "john@doe.com", True)

    permission_provider_id = create_permission_provider(auth_mgr_host, keycloak_user, keycloak_pw)
    permission_id = create_permission(auth_mgr_host, permission_name, '', permission_provider_id, group_id)
    permission_request_id = create_permission_request(auth_mgr_host, user_id, invalidation_date, permission_id)
    approve_permission_request(auth_mgr_host, permission_request_id)

    print('Successfully setup auth management')

    print('Waiting for sync')
    time.sleep(6)

    print('Check if sync worked')


if __name__ == '__main__':
    main()
