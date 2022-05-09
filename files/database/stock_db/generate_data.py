import psycopg2
from psycopg2 import Error
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT
from faker import Faker
from faker_vehicle import VehicleProvider
from random import randint, choice
from uuid import uuid4
from detail_data_parser_results import details_rus, details_eng

PRODUCER_RECORDS = 1000
DETAILS_RECORDS = 5000
STOCK_RECORDS = 200
MAX_DETAILS_IN_STOCK = 10
SWAPS_RECORDS = 100
WORKERS_RECORDS = 10
STOCK_LOG_RECORDS = 10000

# reads from file
def get_part_names():
    res = []
    with open("part_names", "r") as f:
        res.append(f.readline()[1:-1])
        
    return res
        
        
def generate_producers(connection):
    fake = Faker()
    fake.add_provider(VehicleProvider)

    for i in range(PRODUCER_RECORDS):
        name = fake.company()
        country = fake.country().replace("\'", "")
        sql_insert = f"""INSERT INTO T_PRODUCERS (name, country) 
                         VALUES (\'{name}\', \'{country}\');"""
        cursor.execute(sql_insert)
        connection.commit()

def generate_details(connection):
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
    
    return part_names

def generate_stock(connection, part_names):
    for i in range(STOCK_RECORDS):
        part_index = randint(0, DETAILS_RECORDS - 1)
        qty = randint(0, MAX_DETAILS_IN_STOCK)
        sql_insert = f"""INSERT INTO T_STOCK (detail_part_name, quantity) 
                         VALUES (\'{part_names[part_index]}\', {qty});"""
        cursor.execute(sql_insert)
        connection.commit()

def generate_swaps(connection, part_names):
    for i in range(SWAPS_RECORDS):
        src_index = randint(0, DETAILS_RECORDS - 1)
        dst_index = randint(0, DETAILS_RECORDS - 1)
        sql_insert = f"""INSERT INTO T_SWAPS (source_detail, destination_detail) 
                         VALUES (\'{part_names[src_index]}\', \'{part_names[dst_index]}\');"""
        cursor.execute(sql_insert)
        connection.commit()

def generate_workers(connection):
    fake = Faker(['ru_RU'])
    for i in range(WORKERS_RECORDS):
        name, surname = fake.first_name(), fake.last_name()
        birthdate = fake.date_of_birth()
        privilege_level = randint(1, 4)
        username = fake.email()
        password = fake.sha256()
        sql_insert = f"""INSERT INTO T_WORKERS (name, surname, birthdate, privilege_level, username, password) 
                         VALUES (\'{name}\', \'{surname}\', \'{birthdate}\', {privilege_level}, \'{username}\', \'{password}\');"""
        cursor.execute(sql_insert)
        connection.commit()

def generate_log(connection, details):
    for _ in range(STOCK_LOG_RECORDS):
        detail = choice(details)
        worker = randint(1, WORKERS_RECORDS)
        change = randint(-5, 5)
        if (change == 0):
            change = 1
        sql_insert = f"""INSERT INTO T_STOCK_LOG (fk_worker, fk_detail, change) 
                         VALUES ({worker}, \'{detail}\', {change});"""
        cursor.execute(sql_insert)
        connection.commit()
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

    generate_producers(connection)
    part_names = generate_details(connection)
    # generate_stock(connection, part_names)
    generate_swaps(connection, part_names)
    generate_workers(connection)
    # generate_log(connection, get_part_names())

except (Exception, Error) as error:
    print("Ошибка при работе с PostgreSQL", error)
