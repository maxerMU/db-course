#!/bin/bash

mkdir -p report
rm -rf report/*

for i in {1..100}
do
  container=$(sudo docker run -v /home/max/repos/db-course/src/benchmark/report:/report -dt maxermu/stock_running_env);
  echo $container
  sudo docker exec -it $container /bin/bash -c "/app/benchmark/benchmark_session.sh";
  sudo docker container stop $container;
  sudo docker container rm $container;
done

python3 handle_results.py