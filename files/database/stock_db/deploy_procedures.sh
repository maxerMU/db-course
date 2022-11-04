for file in ./procedures/*.sql
do
    psql "sslmode=disable user=postgres hostaddr=$1 port=5432 password=Pass2022!" < $file;
done
