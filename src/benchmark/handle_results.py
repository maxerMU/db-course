RESULTS_PATH = "report/report"

def mid(array):
    s = 0
    for el in array:
        s += el
    
    return s / len(array) if len(array) else 0

asio_fast = []
asio_slow = []
oatpp_fast = []
oatpp_slow = []
with open(RESULTS_PATH, "r") as f:
    for line in f:
        res = line.split(",")
        asio_fast.append(float(res[0]))
        asio_slow.append(float(res[1]))
        oatpp_fast.append(float(res[2]))
        oatpp_slow.append(float(res[3]))

print("==================== RESULTS ====================")
print(f"boost asio fast: {mid(asio_fast)}")
print(f"boost asio slow: {mid(asio_slow)}")
print(f"oatpp fast: {mid(oatpp_fast)}")
print(f"oatpp slow: {mid(oatpp_slow)}")
print("=================================================")
