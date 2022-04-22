import psycopg2
from psycopg2 import Error
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT
from faker import Faker
from faker_vehicle import VehicleProvider
from random import randint
from uuid import uuid4
from detail_data_parser_results import details_rus, details_eng

PRODUCER_RECORDS = 1000
DETAILS_RECORDS = 5000
STOCK_RECORDS = 200
MAX_DETAILS_IN_STOCK = 10
SWAPS_RECORDS = 100

try:
    # Подключение к существующей базе данных
    connection = psycopg2.connect(database="stock_db",
                                  user="stock_adm",
                                  # пароль, который указали при установке PostgreSQL
                                  password="stock_adm",
                                  host="127.0.0.1",
                                  port="5432")
    connection.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
    # Курсор для выполнения операций с базой данных
    cursor = connection.cursor()

    fake = Faker()
    fake.add_provider(VehicleProvider)

    for i in range(PRODUCER_RECORDS):
        name = fake.company()
        country = fake.country().replace("\'", "")
        sql_insert = f"""INSERT INTO T_PRODUCERS (name, country) 
                         VALUES (\'{name}\', \'{country}\');"""
        cursor.execute(sql_insert)
        connection.commit()
    
    part_names = []
    for i in range(DETAILS_RECORDS):
        part_name = uuid4()
        part_names.append(part_name)
        part_index = randint(0, len(details_rus) -1)
        name_rus = details_rus[part_index]
        name_eng = details_eng[part_index]
        producer_id = randint(1, PRODUCER_RECORDS)
        sql_insert = f"""INSERT INTO T_DETAILS (part_name, name_rus, name_eng, producer_id) 
                         VALUES (\'{part_name}\', \'{name_rus}\', \'{name_eng}\', {producer_id});"""
        cursor.execute(sql_insert)
        connection.commit()
    
    for i in range(STOCK_RECORDS):
        part_index = randint(0, DETAILS_RECORDS - 1)
        qty = randint(0, MAX_DETAILS_IN_STOCK)
        sql_insert = f"""INSERT INTO T_STOCK (detail_part_name, quantity) 
                         VALUES (\'{part_names[part_index]}\', {qty});"""
        cursor.execute(sql_insert)
        connection.commit()

    for i in range(SWAPS_RECORDS):
        src_index = randint(0, DETAILS_RECORDS - 1)
        dst_index = randint(0, DETAILS_RECORDS - 1)
        sql_insert = f"""INSERT INTO T_SWAPS (source_detail, destination_detail) 
                         VALUES (\'{part_names[src_index]}\', \'{part_names[dst_index]}\');"""
        cursor.execute(sql_insert)
        connection.commit()

except (Exception, Error) as error:
    print("Ошибка при работе с PostgreSQL", error)
