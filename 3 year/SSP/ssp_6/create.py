import sqlite3

def create_tables():
    connection_params = {"database": "clinic.db"}

    connect = sqlite3.connect(connection_params["database"])
    cursor = connect.cursor()

    cursor.execute("PRAGMA foreign_keys = ON;")

    cursor.execute("DROP TABLE IF EXISTS Посещения;")
    cursor.execute("DROP TABLE IF EXISTS Пациенты;")
    cursor.execute("DROP TABLE IF EXISTS Врачи;")

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Пациенты (
            id_patient INTEGER PRIMARY KEY AUTOINCREMENT,
            full_name TEXT NOT NULL,
            birth_date TEXT NOT NULL,
            phone TEXT,
            address TEXT,
            medical_card TEXT
        )
    ''')

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Врачи (
            id_doctor INTEGER PRIMARY KEY AUTOINCREMENT,
            full_name TEXT NOT NULL,
            specialization TEXT NOT NULL,
            work_schedule TEXT
        )
    ''')

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS Посещения (
            id_visit INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            visit_date TEXT NOT NULL,
            diagnosis TEXT,
            is_confirmed INTEGER DEFAULT 0,
            FOREIGN KEY(patient_id) REFERENCES Пациенты(id_patient) ON DELETE CASCADE,
            FOREIGN KEY(doctor_id) REFERENCES Врачи(id_doctor) ON DELETE CASCADE
        )
    ''')

    cursor.executemany('''
        INSERT INTO Пациенты (full_name, birth_date, phone, address, medical_card) 
        VALUES (?, ?, ?, ?, ?)''',
        [
            ('Иванов Иван Иванович', '1985-05-15', '+375291234567', 'ул. Ленина 15', 'Карта №123'),
            ('Петрова Мария Сергеевна', '1990-12-24', '+375337654321', 'пр. Победителей 20', 'Карта №456'),
        ]
    )

    cursor.executemany('''
        INSERT INTO Врачи (full_name, specialization, work_schedule) 
        VALUES (?, ?, ?)''',
        [
            ('Сидоров Петр Алексеевич', 'Терапевт', 'Пн-Пт 8:00-16:00'),
            ('Козлова Анна Викторовна', 'Хирург', 'Вт-Сб 9:00-17:00'),
        ]
    )

    cursor.executemany('''
        INSERT INTO Посещения (patient_id, doctor_id, visit_date, diagnosis, is_confirmed) 
        VALUES (?, ?, ?, ?, ?)''',
        [
            (1, 1, '2023-11-01 09:00', 'ОРВИ', 1),
            (2, 2, '2023-11-02 10:30', 'Консультация', 0),
        ]
    )

    connect.commit()
    cursor.close()
    connect.close()

if __name__ == "__main__":
    create_tables()
    print("База данных поликлиники успешно создана!")