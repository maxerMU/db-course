psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./init/create_database.sql

psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./init/create_users.sql

psql "sslmode=disable user=stock_adm hostaddr=127.0.0.1 port=5432 password=stock_adm" < ./v0001_0000.sql
