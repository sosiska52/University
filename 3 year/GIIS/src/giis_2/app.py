import tkinter as tk
from tkinter import filedialog, messagebox
import pandas as pd
from tkinter import ttk


class DataFrameViewer(tk.Tk):
    def __init__(self):
        super().__init__()

        # Настройка полноэкранного режима
        self.attributes('-fullscreen', True)
        self.bind("<Escape>", self.exit_program)  # Закрытие программы при нажатии Esc

        self.title("Просмотр таблицы Pandas")

        # Создание меню
        self.menu = tk.Menu(self)
        self.config(menu=self.menu)

        # Меню "File"
        file_menu = tk.Menu(self.menu, tearoff=0)
        file_menu.add_command(label="Load CSV", command=self.load_csv)
        file_menu.add_command(label="Save Visualization", command=self.load_csv)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.exit_program)
        self.menu.add_cascade(label="File", menu=file_menu)

        # Меню "Visualisation"
        visualisation_menu = tk.Menu(self.menu, tearoff=0)
        visualisation_menu.add_command(label="Some Visualisation", command=self.show_inf)  # Пример команды
        self.menu.add_cascade(label="Visualisation", menu=visualisation_menu)

        # Меню "Info"
        info_menu = tk.Menu(self.menu, tearoff=0)
        info_menu.add_command(label="Show Info", command=self.show_inf)
        self.menu.add_cascade(label="Info", menu=info_menu)

        # Фрейм для таблицы
        self.frame = tk.Frame(self)
        self.frame.pack(expand=True, fill='both')

        # Таблица для отображения данных
        self.tree = ttk.Treeview(self.frame, show='headings')
        self.tree.pack(expand=True, fill='both')

        # Разделитель для управления высотой
        self.separator = tk.Frame(self, height=self.winfo_height() // 2)
        self.separator.pack(fill='x')

    def show_inf(self):
        messagebox.showinfo("Информация", "inf")

    def load_csv(self):
        file_path = filedialog.askopenfilename(filetypes=[("CSV files", "*.csv")])
        if file_path:
            try:
                df = pd.read_csv(file_path)
                self.display_dataframe(df)
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось загрузить файл: {e}")

    def display_dataframe(self, df):
        self.tree.delete(*self.tree.get_children())

        self.tree["columns"] = list(df)

        for column in df:
            self.tree.heading(column, text=column)
            self.tree.column(column, anchor="center")

        for index, row in df.iterrows():
            self.tree.insert("", "end", values=list(row[0:]))  # Добавляем все, кроме первого значения

        self.adjust_column_widths()

    def adjust_column_widths(self):
        total_width = self.winfo_width()
        num_columns = len(self.tree["columns"])
        if num_columns > 0:
            column_width = total_width // num_columns
            for column in self.tree["columns"]:
                self.tree.column(column, width=column_width)

    def exit_program(self, event=None):
        self.quit()


if __name__ == "__main__":
    app = DataFrameViewer()
    app.mainloop()