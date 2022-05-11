psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./drop_tables.sql
psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./v0001_0000.sql
psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./v0001_0001.sql
psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./v0001_0002.sql
psql "sslmode=disable user=postgres hostaddr=127.0.0.1 port=5432 password=Pass2022!" < ./grants/grants.sql