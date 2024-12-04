import sqlite3

def create_tables():
    connection_params = {"database": "mydb.sqlite3"}

    connect = sqlite3.connect(connection_params["database"])
    cursor = connect.cursor()

    # Удаление существующих таблиц
    cursor.execute("DROP TABLE IF EXISTS Дело;")
    cursor.execute("DROP TABLE IF EXISTS Подсудимый;")
    cursor.execute("DROP TABLE IF EXISTS Адвокат;")
    cursor.execute("DROP TABLE IF EXISTS Прокурор;")
    cursor.execute("DROP TABLE IF EXISTS Судья;")

    # Создание таблицы Дело
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Дело (
            ID_дела INTEGER PRIMARY KEY,
            Название_дела TEXT,
            Дата_открытия DATE,
            Статус_дела TEXT,
            Статья INTEGER
        )
    ''')

    # Вставка тестовых данных для Дело
    cursor.execute('''
        INSERT INTO Дело (ID_дела, Название_дела, Дата_открытия, Статус_дела, Статья) VALUES
        (1, 'Уголовное дело №1', '2023-01-15', 'В процессе', 158),
        (2, 'Гражданское дело №2', '2023-02-20', 'Закрыто', 111),
        (3, 'Административное дело №3', '2023-03-10', 'В процессе', 20),
        (4, 'Уголовное дело №4', '2023-04-05', 'В процессе', 227),
        (5, 'Гражданское дело №5', '2023-05-12', 'Закрыто', 34)
    ''')

    # Создание таблицы Подсудимый
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Подсудимый (
            ID_подсудимого INTEGER PRIMARY KEY,
            ФИО TEXT,
            Дата_рождения DATE,
            Гражданство TEXT,
            ID_дела INTEGER,
            FOREIGN KEY (ID_дела) REFERENCES Дело(ID_дела)
        )
    ''')

    # Вставка тестовых данных для Подсудимый
    cursor.execute('''
        INSERT INTO Подсудимый (ID_подсудимого, ФИО, Дата_рождения, Гражданство, ID_дела) VALUES
        (1, 'Иванов Иван Иванович', '1990-05-12', 'Беларусь', 1),
        (2, 'Петров Петр Петрович', '1985-08-22', 'Россия', 1),
        (3, 'Смирнова Анна Сергеевна', '1995-11-30', 'Украина', 2),
        (4, 'Козлов Алексей Владимирович', '1988-01-15', 'Беларусь', 3),
        (5, 'Лебедева Мария Николаевна', '1992-03-25', 'Польша', 4)
    ''')

    # Создание таблицы Адвокат
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Адвокат (
            ID_адвоката INTEGER PRIMARY KEY,
            ФИО TEXT,
            Контактный_номер TEXT,
            ID_дела INTEGER,
            FOREIGN KEY (ID_дела) REFERENCES Дело(ID_дела)
        )
    ''')

    # Вставка тестовых данных для Адвокат
    cursor.execute('''
        INSERT INTO Адвокат (ID_адвоката, ФИО, Контактный_номер, ID_дела) VALUES
        (1, 'Ковалёва Ольга Ивановна', '+375291234567', 1),
        (2, 'Сидоров Дмитрий Васильевич', '+375291234568', 2),
        (3, 'Федорова Наталья Сергеевна', '+375291234569', 3),
        (4, 'Никитина Elena Петровна', '+375291234570', 4),
        (5, 'Морозов Сергей Александрович', '+375291234571', 5)
    ''')

    # Создание таблицы Прокурор
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Прокурор (
            ID_прокурора INTEGER PRIMARY KEY,
            ФИО TEXT,
            Контактный_номер TEXT,
            ID_дела INTEGER,
            FOREIGN KEY (ID_дела) REFERENCES Дело(ID_дела)
        )
    ''')

    # Вставка тестовых данных для Прокурор
    cursor.execute('''
        INSERT INTO Прокурор (ID_прокурора, ФИО, Контактный_номер, ID_дела) VALUES
        (1, 'Орлов Максим Александрович', '+375291234572', 1),
        (2, 'Ильин Виктор Дмитриевич', '+375291234573', 2),
        (3, 'Лебедева Екатерина Владимировна', '+375291234574', 3),
        (4, 'Тихонов Сергей Александрович', '+375291234575', 4),
        (5, 'Васильева Анна Николаевна', '+375291234576', 5)
    ''')

    # Создание таблицы Судья
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Судья (
            ID_судьи INTEGER PRIMARY KEY,
            ФИО TEXT,
            Судебный_участок TEXT,
            ID_дела INTEGER,
            FOREIGN KEY (ID_дела) REFERENCES Дело(ID_дела)
        )
    ''')

    # Вставка тестовых данных для Судья
    cursor.execute('''
        INSERT INTO Судья (ID_судьи, ФИО, Судебный_участок, ID_дела) VALUES
        (1, 'Николаев Александр Сергеевич', 'Участок №1', 1),
        (2, 'Павлова Юлия Андреевна', 'Участок №2', 2),
        (3, 'Тихонов Сергей Владимирович', 'Участок №3', 3),
        (4, 'Сидорова Анна Павловна', 'Участок №4', 4),
        (5, 'Федоров Иван Николаевич', 'Участок №5', 5)
    ''')

    connect.commit()
    cursor.close()
    connect.close()

if __name__ == "__main__":
    create_tables()

    print("Tables created and data inserted successfully.")