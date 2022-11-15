psql -h $2 "sslmode=disable user=$1 port=$3 password=$4" < ./init/create_database.sql

psql -h $2 "sslmode=disable user=$1 port=$3 password=$4" < ./init/create_users.sql
