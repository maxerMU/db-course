# Балансировка нагрузки 2:1:1

This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /api/v1/details
Document Length:        815182 bytes

Concurrency Level:      2
Time taken for tests:   4.625 seconds
Complete requests:      100
Failed requests:        0
Total transferred:      81533700 bytes
HTML transferred:       81518200 bytes
Requests per second:    21.62 [#/sec] (mean)
Time per request:       92.504 [ms] (mean)
Time per request:       46.252 [ms] (mean, across all concurrent requests)
Transfer rate:          17214.95 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:    79   91  13.4     87     156
Waiting:       78   87   9.1     86     155
Total:         79   91  13.4     87     156

Percentage of the requests served within a certain time (ms)
  50%     87
  66%     89
  75%     90
  80%     91
  90%    105
  95%    130
  98%    134
  99%    156
 100%    156 (longest request)


 # Без балансировки

This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /api/v1/details
Document Length:        815182 bytes

Concurrency Level:      1
Time taken for tests:   8.330 seconds
Complete requests:      100
Failed requests:        0
Total transferred:      81533700 bytes
HTML transferred:       81518200 bytes
Requests per second:    12.01 [#/sec] (mean)
Time per request:       83.295 [ms] (mean)
Time per request:       83.295 [ms] (mean, across all concurrent requests)
Transfer rate:          9559.09 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:    75   83  10.3     80     131
Waiting:       74   80   6.4     79     111
Total:         75   83  10.3     80     131

Percentage of the requests served within a certain time (ms)
  50%     80
  66%     82
  75%     84
  80%     85
  90%     91
  95%    112
  98%    121
  99%    131
 100%    131 (longest request)


 # Вывод

 RPS при балансировке больше, чем без нее. Результат отличается не сильно, так как все серверы обращаются к одной базе данных
