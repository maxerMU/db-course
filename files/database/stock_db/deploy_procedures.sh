for file in ./procedures/*.sql
do
    psql "sslmode=disable user=$1 hostaddr=$2 port=$3 password=$4" < $file;
done
