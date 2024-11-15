import sqlite3

def create_tables():
    connection_params = {"database": "mydb.sqlite3"}

    connect = sqlite3.connect(connection_params["database"])
    cursor = connect.cursor()

    cursor.execute("DROP TABLE IF EXISTS Таблица_1;")
    cursor.execute("DROP TABLE IF EXISTS Таблица_2;")
    cursor.execute("DROP TABLE IF EXISTS Таблица_3;")

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Таблица_1 (
            N_клиента INTEGER PRIMARY KEY,
            ФИО TEXT,
            Телефон TEXT,
            Адрес TEXT
        )
    ''')

    cursor.execute('''
        INSERT INTO Таблица_1 (N_клиента, ФИО, Телефон, Адрес) VALUES
        (1, 'Иванов Иван', '+375336679407', 'Брест, ул. Ленина, д. 1'),
        (2, 'Петрова Мария', '+375336959907', 'Гродно, пр. Невский, д. 2'),
        (3, 'Сидоров Петр', '+375291279499', 'Минск, ул. Мира, д. 3')
    ''')

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Таблица_2 (
            N_клиента INTEGER,
            N_фильма INTEGER,
            Дата TEXT,
            PRIMARY KEY (N_клиента, N_фильма)
        )
    ''')

    cursor.execute('''
        INSERT INTO Таблица_2 (N_клиента, N_фильма, Дата) VALUES
        (1, 1, '2023-11-01'),
        (2, 2, '2023-11-02'),
        (3, 3, '2023-11-03')
    ''')

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Таблица_3 (
            N_фильма INTEGER PRIMARY KEY,
            Режиссер TEXT,
            Название TEXT,
            Год_выпуска INTEGER
        )
    ''')

    cursor.execute('''
        INSERT INTO Таблица_3 (N_фильма, Режиссер, Название, Год_выпуска) VALUES
        (1, 'Тарантино Квентин', 'Убить Билла', 2003),
        (2, 'Нолан Кристофер', 'Начало', 2010),
        (3, 'Кэмерон Джеймс', 'Аватар', 2009)
    ''')

    connect.commit()
    cursor.close()
    connect.close()

if __name__ == "__main__":
    create_tables()

    print("Tables created and data inserted successfully.")