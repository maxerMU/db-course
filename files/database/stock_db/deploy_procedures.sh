for file in ./procedures/*.sql
do
    psql -h $2 "sslmode=disable user=$1 port=$3 password=$4" < $file;
done
