psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./drop_tables.sql
psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./v0001_0000.sql
psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./v0001_0001.sql
psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./v0001_0002.sql
psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./grants/grants.sql
