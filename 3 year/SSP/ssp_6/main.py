import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import sqlite3
from datetime import datetime


class ClinicApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Система учета посещений поликлиники")
        self.master.geometry("1200x800")

        self.conn = sqlite3.connect('clinic.db')
        self.conn.execute("PRAGMA foreign_keys = ON;")

        self.create_widgets()
        self.load_data()

    def create_widgets(self):
        self.notebook = ttk.Notebook(self.master)

        self.patients_frame = ttk.Frame(self.notebook)
        self.doctors_frame = ttk.Frame(self.notebook)
        self.visits_frame = ttk.Frame(self.notebook)

        self.create_table(self.patients_frame, "Пациенты",
                          ['id_patient', 'full_name', 'birth_date', 'phone', 'address', 'medical_card'])
        self.create_table(self.doctors_frame, "Врачи",
                          ['id_doctor', 'full_name', 'specialization', 'work_schedule'])
        self.create_table(self.visits_frame, "Посещения",
                          ['id_visit', 'patient_id', 'doctor_id', 'visit_date', 'diagnosis', 'is_confirmed'])

        self.notebook.add(self.patients_frame, text="Пациенты")
        self.notebook.add(self.doctors_frame, text="Врачи")
        self.notebook.add(self.visits_frame, text="Посещения")
        self.notebook.pack(expand=True, fill='both')

    def create_table(self, parent, table_name, columns):
        tree = ttk.Treeview(parent, columns=columns, show='headings', selectmode='browse')

        for col in columns:
            tree.heading(col, text=col.replace('_', ' ').title())
            tree.column(col, width=120, anchor='center')

        scrollbar = ttk.Scrollbar(parent, orient="vertical", command=tree.yview)
        tree.configure(yscrollcommand=scrollbar.set)

        btn_frame = ttk.Frame(parent)
        ttk.Button(btn_frame, text="Добавить", command=lambda: self.add_record(table_name)).pack(side=tk.LEFT, padx=5)
        ttk.Button(btn_frame, text="Редактировать", command=lambda: self.edit_record(table_name, tree)).pack(
            side=tk.LEFT, padx=5)
        ttk.Button(btn_frame, text="Удалить", command=lambda: self.delete_record(table_name, tree)).pack(side=tk.LEFT,
                                                                                                         padx=5)
        ttk.Button(btn_frame, text="Обновить", command=self.load_data).pack(side=tk.LEFT, padx=5)

        tree.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        btn_frame.pack(side=tk.BOTTOM, pady=5)

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

    def add_record(self, table_name):
        dialog = tk.Toplevel(self.master)
        dialog.title(f"Добавить запись в {table_name}")

        cursor = self.conn.execute(f"PRAGMA table_info({table_name})")
        columns_info = cursor.fetchall()

        columns = [col[1] for col in columns_info if not col[1].startswith('id_')]

        entries = {}
        for i, col in enumerate(columns):
            tk.Label(dialog, text=col.replace('_', ' ').title()).grid(row=i, column=0, padx=5, pady=5)

            if col == 'visit_date':
                entry = ttk.Entry(dialog)
                entry.insert(0, datetime.now().strftime("%Y-%m-%d %H:%M"))
            elif col == 'is_confirmed':
                var = tk.IntVar()
                entry = ttk.Checkbutton(dialog, variable=var)
                entries[col] = var
                continue
            else:
                entry = ttk.Entry(dialog)

            entry.grid(row=i, column=1, padx=5, pady=5)
            entries[col] = entry

        def save():
            try:
                values = []
                for col in columns:
                    if col == 'is_confirmed':
                        values.append(entries[col].get())
                    else:
                        values.append(entries[col].get())

                placeholders = ', '.join(['?' for _ in columns])
                self.conn.execute(
                    f"INSERT INTO {table_name} ({', '.join(columns)}) VALUES ({placeholders})",
                    values
                )
                self.conn.commit()
                self.load_data()
                dialog.destroy()
                messagebox.showinfo("Успех", "Запись успешно добавлена")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось добавить запись: {str(e)}")

        ttk.Button(dialog, text="Сохранить", command=save).grid(row=len(columns), columnspan=2, pady=10)

    def edit_record(self, table_name, tree):
        selected = tree.selection()
        if not selected:
            messagebox.showwarning("Внимание", "Выберите запись для редактирования!")
            return

        item = tree.item(selected[0])
        values = item['values']

        dialog = tk.Toplevel(self.master)
        dialog.title(f"Редактировать запись в {table_name}")

        cursor = self.conn.execute(f"PRAGMA table_info({table_name})")
        columns = [col[1] for col in cursor.fetchall()]

        entries = {}
        for i, col in enumerate(columns):
            tk.Label(dialog, text=col.replace('_', ' ').title()).grid(row=i, column=0, padx=5, pady=5)

            if col.startswith('id_'):
                tk.Label(dialog, text=str(values[i])).grid(row=i, column=1, padx=5, pady=5)
            elif col == 'is_confirmed':
                var = tk.IntVar(value=values[i])
                entry = ttk.Checkbutton(dialog, variable=var)
                entry.grid(row=i, column=1, padx=5, pady=5)
                entries[col] = var
            else:
                entry = ttk.Entry(dialog)
                entry.insert(0, values[i])
                entry.grid(row=i, column=1, padx=5, pady=5)
                entries[col] = entry

        def save():
            try:
                new_values = []
                for col in columns:
                    if col in entries:
                        if col == 'is_confirmed':
                            new_values.append(entries[col].get())
                        else:
                            new_values.append(entries[col].get())
                    else:
                        new_values.append(values[columns.index(col)])

                set_clause = ', '.join([f"{col} = ?" for col in columns])
                where_clause = f"{columns[0]} = ?"
                self.conn.execute(
                    f"UPDATE {table_name} SET {set_clause} WHERE {where_clause}",
                    new_values + [values[0]]
                )
                self.conn.commit()
                self.load_data()
                dialog.destroy()
                messagebox.showinfo("Успех", "Запись успешно обновлена")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось обновить запись: {str(e)}")

        ttk.Button(dialog, text="Сохранить", command=save).grid(row=len(columns), columnspan=2, pady=10)

    def delete_record(self, table_name, tree):
        selected = tree.selection()
        if not selected:
            messagebox.showwarning("Внимание", "Выберите запись для удаления!")
            return

        if messagebox.askyesno("Подтверждение", "Вы уверены, что хотите удалить эту запись?"):
            item = tree.item(selected[0])
            id_value = item['values'][0]

            if table_name == "Пациенты":
                primary_key = "id_patient"
            elif table_name == "Врачи":
                primary_key = "id_doctor"
            elif table_name == "Посещения":
                primary_key = "id_visit"
            else:
                messagebox.showerror("Ошибка", "Неизвестная таблица!")
                return

            try:
                self.conn.execute(f"DELETE FROM {table_name} WHERE {primary_key} = ?", (id_value,))
                self.conn.commit()
                self.load_data()
                messagebox.showinfo("Успех", "Запись успешно удалена")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось удалить запись: {str(e)}")

    def __del__(self):
        if hasattr(self, 'conn'):
            self.conn.close()


if __name__ == "__main__":
    root = tk.Tk()
    app = ClinicApp(root)
    root.mainloop()