import requests
from time import time

BOOST_ASIO_BASE_URL = "http://localhost:8020"
FAST_REQ_URL = "/test1"
SLOW_REQ_URL = "/test2"

def benchmark(url):
    start = time()

    requests.get(url)

    end = time()

    return end - start


def main():
    res = benchmark(BOOST_ASIO_BASE_URL + FAST_REQ_URL)
    print(res)

    res = benchmark(BOOST_ASIO_BASE_URL + SLOW_REQ_URL)
    print(res)


if __name__ == "__main__":
    main()