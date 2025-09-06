import tkinter as tk
from tkinter import messagebox

class HashTable:
    def __init__(self, size=100):
        self.size = size
        self.table = [None] * size
        self.collisions = 0

    def hash_function(self, key):
        if len(key) < 2:
            return ord(key[0]) % self.size
        temp = ord(key[0]) + ord(key[1])
        return temp % self.size

    def add(self, key):
        index = self.hash_function(key)
        while self.table[index] is not None:
            index += 1
            self.collisions += 1
        self.table[index] = key

    def remove(self, key):
        index = self.hash_function(key)
        while index < self.size:
            if self.table[index] == key:
                self.table[index] = None
                return
            index += 1
            self.collisions += 1


class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Hash Table")

        self.hash_table = HashTable()

        self.left_frame = tk.Frame(self.root)
        self.left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        self.right_frame = tk.Frame(self.root)
        self.right_frame.pack(side=tk.RIGHT, fill=tk.Y)

        self.table_display = tk.Text(self.left_frame, width=30)
        self.table_display.pack(fill=tk.BOTH, expand=True)

        self.add_button = tk.Button(self.right_frame, text="Добавить", command=self.add_word)
        self.add_button.pack(pady=10)

        self.remove_button = tk.Button(self.right_frame, text="Удалить", command=self.remove_word)
        self.remove_button.pack(pady=10)

        self.collisions_label = tk.Label(self.right_frame, text="Коллизии: 0")
        self.collisions_label.pack(pady=10)

        self.update_display()

    def add_word(self):
        word = self.prompt_for_input("Введите слово для добавления:")
        if word:
            self.hash_table.collisions = 0
            self.hash_table.add(word)
            self.update_display()
            self.collisions_label.config(text=f"Коллизии: {self.hash_table.collisions}")

    def remove_word(self):
        word = self.prompt_for_input("Введите слово для удаления:")
        if word:
            self.hash_table.collisions = 0
            self.hash_table.remove(word)
            self.update_display()
            self.collisions_label.config(text=f"Коллизии: {self.hash_table.collisions}")

    def prompt_for_input(self, message):
        input_window = tk.Toplevel(self.root)
        input_window.title(message)

        entry = tk.Entry(input_window)
        entry.pack(pady=10)

        result = None

        def on_submit():
            nonlocal result
            result = entry.get()
            input_window.destroy()

        submit_button = tk.Button(input_window, text="OK", command=on_submit)
        submit_button.pack(pady=10)

        self.root.wait_window(input_window)
        return result

    def update_display(self):
        self.table_display.delete(1.0, tk.END)
        for index, value in enumerate(self.hash_table.table):
            self.table_display.insert(tk.END, f"{index}: {value}\n")


if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()