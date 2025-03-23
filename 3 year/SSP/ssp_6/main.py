# [file name]: main.py
import tkinter as tk
from tkinter import ttk, messagebox
import sqlite3
from tkinter import simpledialog


class ClinicApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Система учета посещений поликлиники")
        self.master.geometry("1200x800")

        self.conn = sqlite3.connect('clinic.db')
        self.conn.execute("PRAGMA foreign_keys = ON;")  # Включаем поддержку внешних ключей
        self.create_widgets()
        self.load_data()

    def create_widgets(self):
        # Панель вкладок
        self.notebook = ttk.Notebook(self.master)

        # Вкладка пациентов
        self.patients_frame = ttk.Frame(self.notebook)
        self.create_table(self.patients_frame, "Пациенты",
                          ['id_patient', 'full_name', 'birth_date', 'phone', 'address', 'medical_card'])

        # Вкладка врачей
        self.doctors_frame = ttk.Frame(self.notebook)
        self.create_table(self.doctors_frame, "Врачи",
                          ['id_doctor', 'full_name', 'specialization', 'work_schedule'])

        # Вкладка посещений
        self.visits_frame = ttk.Frame(self.notebook)
        self.create_table(self.visits_frame, "Посещения",
                          ['id_visit', 'patient_id', 'doctor_id', 'visit_date', 'diagnosis', 'is_confirmed'])

        self.notebook.add(self.patients_frame, text="Пациенты")
        self.notebook.add(self.doctors_frame, text="Врачи")
        self.notebook.add(self.visits_frame, text="Посещения")
        self.notebook.pack(expand=True, fill='both')

    def create_table(self, parent, table_name, columns):
        # Treeview для отображения данных
        tree = ttk.Treeview(parent, columns=columns, show='headings', selectmode='browse')

        # Настройка колонок
        for col in columns:
            tree.heading(col, text=col.replace('_', ' ').title())
            tree.column(col, width=120, anchor='center')

        # Полоса прокрутки
        scrollbar = ttk.Scrollbar(parent, orient="vertical", command=tree.yview)
        tree.configure(yscrollcommand=scrollbar.set)

        # Кнопки управления
        btn_frame = ttk.Frame(parent)
        ttk.Button(btn_frame, text="Добавить", command=lambda: self.add_record(table_name)).pack(side=tk.LEFT, padx=5)
        ttk.Button(btn_frame, text="Редактировать", command=lambda: self.edit_record(table_name, tree)).pack(
            side=tk.LEFT, padx=5)
        ttk.Button(btn_frame, text="Удалить", command=lambda: self.delete_record(table_name, tree)).pack(side=tk.LEFT,
                                                                                                         padx=5)
        ttk.Button(btn_frame, text="Обновить", command=self.load_data).pack(side=tk.LEFT, padx=5)

        # Размещение элементов
        tree.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        btn_frame.pack(side=tk.BOTTOM, pady=5)

        # Сохраняем ссылку на treeview
        setattr(self, f"{table_name.lower()}_tree", tree)

    def load_data(self):
        for table in self.notebook.tabs():
            frame = self.notebook.nametowidget(table)
            tree = frame.winfo_children()[0]
            table_name = self.notebook.tab(table, "text")

            tree.delete(*tree.get_children())
            cursor = self.conn.execute(f"SELECT * FROM {table_name}")
            for row in cursor:
                tree.insert('', 'end', values=row)

    def delete_record(self, table_name, tree):
        selected = tree.selection()
        if not selected:
            messagebox.showwarning("Внимание", "Выберите запись для удаления!")
            return

        if messagebox.askyesno("Подтверждение", "Удалить выбранную запись?"):
            item = tree.item(selected)
            id_value = item['values'][0]

            # Определяем имя первичного ключа для каждой таблицы
            if table_name == "Пациенты":
                primary_key = "id_patient"
            elif table_name == "Врачи":
                primary_key = "id_doctor"
            elif table_name == "Посещения":
                primary_key = "id_visit"
            else:
                messagebox.showerror("Ошибка", "Неизвестная таблица!")
                return

            # Выполняем удаление
            self.conn.execute(f"DELETE FROM {table_name} WHERE {primary_key} = ?", (id_value,))
            self.conn.commit()
            self.load_data()

    def __del__(self):
        self.conn.close()


if __name__ == "__main__":
    root = tk.Tk()
    app = ClinicApp(root)
    root.mainloop()