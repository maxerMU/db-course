psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./init/create_database.sql

psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < ./init/create_users.sql
