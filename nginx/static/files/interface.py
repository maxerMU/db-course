import imp
import requests
import json

host = "localhost:8001"
DetailsUrl = f"http://{host}/details"
WorkersUrl = f"http://{host}/workers"
LoginUrl = f"http://{host}/auth/login"
StockUrl = f"http://{host}/stock"

token = ""

def allDetalsHandler():
    headers_ = {"Autharization": token}
    resp = requests.get(DetailsUrl, headers=headers_)
    if resp.status_code == 401:
        print("not authorised")
        return

    resp = json.loads(resp.text)
    details = resp["details"]
    for detail in details:
        print("==============")
        print("name_eng: ", detail["name_eng"])
        print("part_number: ", detail["part_number"])
        print("producer_id: ", detail["producer_id"])
        print("==============")

def getDetail():
    part_number = input("Input part number: ")
    headers_ = {"Autharization": token}
    resp = requests.get(DetailsUrl + f"/{part_number}", headers=headers_)
    if (resp.status_code == 404):
        print("Not found")
    elif resp.status_code == 401:
        print("not authorised")
        return
    else:
        detail = json.loads(resp.text)
        print("name_eng: ", detail["name_eng"])
        print("part_number: ", detail["part_number"])
        print("producer_id: ", detail["producer_id"])

def addDetailHandler():
    part_number = input("Input part number: ")
    name_eng = input("Input name in english: ")
    # name_rus = input("Input name in russian: ")
    producer_id = int(input("Input producer id: "))
    json_obj = {"part_number": part_number, "name_eng": name_eng,
                "name_rus": "russian name", "producer_id": producer_id}
    headers_ = {"Autharization": token}
    resp = requests.post(DetailsUrl, data=json.dumps(json_obj), headers=headers_)
    if resp.status_code == 401:
        print("not authorised")
        return

def removeDetailHandler():
    part_number = input("Input part number: ")
    headers_ = {"Autharization": token}
    resp = requests.delete(DetailsUrl + f"/{part_number}", headers=headers_)
    if resp.status_code == 401:
        print("not authorised")
        return

def updateDetailHandler():
    part_number = input("Input part number: ")
    name_eng = input("Input name in english: ")
    # name_rus = input("Input name in russian: ")
    producer_id = int(input("Input producer id: "))
    json_obj = {"name_eng": name_eng,
                "name_rus": "russian name", "producer_id": producer_id}
    headers_ = {"Autharization": token}
    resp = requests.put(DetailsUrl + f"/{part_number}", data=json.dumps(json_obj), headers=headers_)
    if resp.status_code == 401:
        print("not authorised")
        return

def stockStateHandler():
    headers_ = {"Autharization": token}
    resp = requests.get(StockUrl, headers=headers_)
    if resp.status_code == 401:
        print("not authorised")
        return
    stock_details = json.loads(resp.text)
    details = stock_details["details"]
    if len(details) > 0:
        for detail in details:
            print(detail["part_number"] + " -- " + detail["quantity"])

def loginHandler():
    username = input("input username: ")
    password = input("input password: ")
    json_obj = {"username": username, "password": password}
    resp = requests.post(LoginUrl, data=json.dumps(json_obj))

    global token
    json_obj = json.loads(resp.text)
    token = json_obj["access_token"]
            
handlersMap = {1: allDetalsHandler,
               2: getDetail,
               3: addDetailHandler,
               4: removeDetailHandler,
               5: updateDetailHandler,
               6: stockStateHandler,
               7: loginHandler}

def printMenu():
    print("\n1. Get all Details")
    print("2. Get Detail")
    print("3. Add Detail")
    print("4. Remove Detail")
    print("5. Update Detail")
    print("6. Stock state")
    print("7. Login")
    print("0. Exit")
    print("Yout choice: ", end='')

def mainloop():
    while True:
        printMenu()
        try:
            handlerNumber = int(input())
            if (handlerNumber == 0):
                break
            handler = handlersMap[handlerNumber]
            handler()
        except KeyError:
            print("Incorrect input")

def main():
    mainloop()

if __name__ == "__main__":
    main()