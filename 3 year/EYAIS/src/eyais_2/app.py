import tkinter as tk
from tkinter import ttk, filedialog
from tkinter import simpledialog
import pymorphy3
import docx2txt
import re

class Word:
    def __init__(self, word):
        self.word = word
        self.morphy = []

        morph_analyzer = pymorphy3.MorphAnalyzer()
        parsed_word = morph_analyzer.parse(word)[0]

        tags = [
            {'name': 'Исходная форма', 'value': parsed_word.normal_form},
            {'name': 'Часть речи', 'value': parsed_word.tag.POS},
            {'name': 'Падеж', 'value': parsed_word.tag.case},
            {'name': 'Род', 'value': parsed_word.tag.gender},
            {'name': 'Число', 'value': parsed_word.tag.number},
            {'name': 'Время', 'value': parsed_word.tag.tense},
            {'name': 'Вид', 'value': parsed_word.tag.aspect},
            {'name': 'Лицо', 'value': parsed_word.tag.person},
            {'name': 'Наклонение', 'value': parsed_word.tag.mood},
            {'name': 'Залог', 'value': parsed_word.tag.voice}
        ]

        for tag in tags:
            if tag['value'] is not None:
                self.morphy.append(tag)

class Application(tk.Tk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title("Словарь естественного языка")
        self.geometry("1920x1080")

        self.words = []

        menu_bar = tk.Menu(self)
        self.config(menu=menu_bar)

        # "Файл"
        file_menu = tk.Menu(menu_bar, tearoff=0)
        file_menu.add_command(label="Открыть файл", command=self.select_file)
        file_menu.add_separator()
        file_menu.add_command(label="Выход", command=self.quit)
        menu_bar.add_cascade(label="Файл", menu=file_menu)

        # "Слово"
        word_menu = tk.Menu(menu_bar, tearoff=0)
        word_menu.add_command(label="Добавить слово", command=self.add_word)
        word_menu.add_command(label="Удалить выбранное", command=self.delete_word)
        word_menu.add_command(label="Сгенерировать формы", command=self.generate_forms)
        word_menu.add_command(label="Расстояние Левенштейна", command=self.generate_distance)
        menu_bar.add_cascade(label="Слово", menu=word_menu)

        # "Поиск"
        search_menu = tk.Menu(menu_bar, tearoff=0)
        search_menu.add_command(label="По подстроке", command=self.search_word)
        search_menu.add_command(label="По синтаксису", command=self.search_synaxis)
        menu_bar.add_cascade(label="Поиск", menu=search_menu)

        self.word_listbox = tk.Listbox(self, selectmode=tk.SINGLE)
        self.word_listbox.grid(row=0, column=0, padx=5, pady=5, sticky=tk.W + tk.E + tk.N + tk.S)
        self.word_listbox.bind("<<ListboxSelect>>", self.show_word_info)

        self.word_info_text = tk.Text(self, wrap="word")
        self.word_info_text.grid(row=0, column=1, padx=5, pady=5, sticky=tk.W + tk.E + tk.N + tk.S)

        self.grid_columnconfigure(0, weight=3, uniform="cols")
        self.grid_columnconfigure(1, weight=1, uniform="cols")
        self.grid_rowconfigure(0, weight=1)

    def generate_distance(self):
        selected_index = self.word_listbox.curselection()
        if selected_index:
            selected_word = self.words[selected_index[0]].word
            self.word_info_text.delete(1.0, tk.END)

            for word_object in self.words:
                if word_object.word != selected_word:
                    distance = self.levenshtein_distance(selected_word, word_object.word)
                    self.word_info_text.insert(tk.END, f"Расстояние до слова '{word_object.word}' - {distance}\n")

    def levenshtein_distance(self, s1, s2):
        if len(s1) < len(s2):
            return self.levenshtein_distance(s2, s1)

        if len(s2) == 0:
            return len(s1)

        previous_row = range(len(s2) + 1)
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            for j, c2 in enumerate(s2):
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))
            previous_row = current_row

        return previous_row[-1]

    def search_word(self):
        substring = simpledialog.askstring("Поиск по подстроке", "Введите подстроку:").strip()
        if substring:
            self.word_listbox.delete(0, tk.END)
            filtered_words = [w for w in self.words if substring in w.word]
            for word_object in filtered_words:
                word_info = f"{word_object.word} ({', '.join(tag['value'] for tag in word_object.morphy)})"
                self.word_listbox.insert(tk.END, word_info)

    def search_synaxis(self):
        syntactic_features = [
            'Часть речи', 'Падеж', 'Род', 'Число', 'Время', 'Вид', 'Лицо', 'Наклонение', 'Залог'
        ]
        feature = simpledialog.askstring("Поиск по синтаксису",
                                         "Выберите характеристику:\n" + ", ".join(syntactic_features))
        if feature:
            value = simpledialog.askstring("Поиск по синтаксису", f"Введите значение для '{feature}':")
            if value:
                self.word_listbox.delete(0, tk.END)
                filtered_words = [w for w in self.words if
                                  any(tag['name'] == feature and tag['value'] == value for tag in w.morphy)]
                for word_object in filtered_words:
                    word_info = f"{word_object.word} ({', '.join(tag['value'] for tag in word_object.morphy)})"
                    self.word_listbox.insert(tk.END, word_info)

    def add_word(self):
        word = simpledialog.askstring("Добавить слово", "Введите слово:").strip()

        if word:
            if word not in [w.word for w in self.words]:
                word_object = Word(word)
                self.words.append(word_object)
                self.sort_words_list()
                word_info = f"{word} ({', '.join(tag['value'] for tag in word_object.morphy)})"
                self.word_listbox.insert(tk.END, word_info)

    def delete_word(self):
        selected_index = self.word_listbox.curselection()
        if selected_index:
            del self.words[selected_index[0]]
            self.word_listbox.delete(selected_index)

    def generate_forms(self):
        selected_index = self.word_listbox.curselection()
        if selected_index:
            word = self.words[selected_index[0]].word
            morph_analyzer = pymorphy3.MorphAnalyzer()
            parsed_word = morph_analyzer.parse(word)[0]

            forms = parsed_word.lexeme
            self.word_info_text.delete(1.0, tk.END)
            for form in forms:
                self.word_info_text.insert(tk.END, f"{form.word}\n")

    def select_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("Word files", "*.docx"), ("All files", "*.*")])
        if file_path:
            self.load_from_docx(file_path)

    def load_from_docx(self, filename):
        text = docx2txt.process(filename).lower()

        pattern = re.compile(r'[а-яА-Я]+')
        words = pattern.findall(text)

        for word in words:
            if word not in [w.word for w in self.words]:
                word_object = Word(word)
                self.words.append(word_object)
                self.sort_words_list()
                word_info = f"{word} ({', '.join(tag['value'] for tag in word_object.morphy)})"
                self.word_listbox.insert(tk.END, word_info)

    def sort_words_list(self):
        self.words.sort(key=lambda x: x.word.lower())
        self.word_listbox.delete(0, tk.END)
        for word_object in self.words:
            word_info = f"{word_object.word} ({', '.join(tag['value'] for tag in word_object.morphy)})"
            self.word_listbox.insert(tk.END, word_info)

    def show_word_info(self, event):
        selected_index = self.word_listbox.curselection()
        if selected_index:
            word = self.words[selected_index[0]]
            self.word_info_text.delete(1.0, tk.END)
            for tag in word.morphy:
                self.word_info_text.insert(tk.END, f"{tag['name']}: {tag['value']}\n")

