#!/bin/bash

/app/build/benchmark/boost_asio_on_coroutines/benchmark_asio /app/benchmark/boost_asio_on_coroutines/conf/dummy1.yaml &
/app/build/benchmark/oatpp/oatpp-async-test &
python3 /app/benchmark/benchmarker.py