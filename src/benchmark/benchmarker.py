import requests
from time import time

BOOST_ASIO_BASE_URL = "http://localhost:8020"
OATPP_BASE_URL = "http://localhost:8021"
FAST_REQ_URL = "/test1"
SLOW_REQ_URL = "/test2"

REPORT_PATH = "/report/report"
# REPORT_PATH = "/home/max/repos/db-course/src/benchmark/benchmark_report"

def benchmark(url):
    start = time()

    requests.get(url)

    end = time()

    return end - start


def main():
    res1 = 0
    res2 = 0
    res3 = 0
    res4 = 0
    for i in range(15):
        res1 += benchmark(BOOST_ASIO_BASE_URL + FAST_REQ_URL)
        res2 += benchmark(BOOST_ASIO_BASE_URL + SLOW_REQ_URL)
        res3 += benchmark(OATPP_BASE_URL + FAST_REQ_URL)
        res4 += benchmark(OATPP_BASE_URL + SLOW_REQ_URL)

    with open(REPORT_PATH, "a") as f:
        f.write(f"{res1},{res2},{res3},{res4}\n")


if __name__ == "__main__":
    main()