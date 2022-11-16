import requests

BASE_URL = "http://localhost:8001"
SIGN_UP_URL = BASE_URL + "/workers"
LOGIN_URL = BASE_URL + "/auth/login"
GET_DETAILS_URL = BASE_URL + "/details"

def test_get_details():
    worker = {
        "name": "Ivan",
        "surname": "Pupkin",
        "birthdate": "1994-03-04",
        "username": "ivan10",
        "password": "123456"
    }
    #sign up
    resp = requests.post(SIGN_UP_URL, json=worker)

    assert resp.status_code == requests.codes.ok

    #login
    resp = requests.post(LOGIN_URL, json={
        "username": worker["username"],
        "password": worker["password"]
    })

    assert resp.status_code == requests.codes.ok

    token = resp.json()["access_token"]

    # get details
    headers = { "Authorization" : token }
    resp = requests.get(GET_DETAILS_URL, headers=headers)

    assert resp.status_code == requests.codes.ok