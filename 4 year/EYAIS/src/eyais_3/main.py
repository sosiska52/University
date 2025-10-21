import tkinter as tk
from tkinter import filedialog, scrolledtext, messagebox, ttk
from deep_translator import GoogleTranslator
import threading
import spacy
from collections import Counter

nlp = spacy.load("en_core_web_sm")

class TXTTranslatorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Переводчик TXT (Английский → Немецкий)")
        self.root.geometry("1000x800")

        self.file_content = None           # сюда сохраняем содержимое открытого TXT
        self.stop_translation_flag = False
        self.word_freq_data = None         # сюда сохраняем данные о частоте слов

        self.create_widgets()

    def create_widgets(self):
        control_frame = tk.Frame(self.root)
        control_frame.pack(fill=tk.X, padx=10, pady=10)


        self.open_button = tk.Button(control_frame, text="Открыть TXT", command=self.open_txt, font=("Arial", 12))
        self.open_button.pack(side=tk.LEFT, padx=5)

        self.translate_button = tk.Button(control_frame, text="Перевести", command=self.start_translation_thread,
                                          font=("Arial", 12))
        self.translate_button.pack(side=tk.LEFT, padx=5)

        self.stop_button = tk.Button(control_frame, text="Стоп", command=self.stop_translation, state=tk.DISABLED,
                                     font=("Arial", 12))
        self.stop_button.pack(side=tk.LEFT, padx=5)

        language_label = tk.Label(control_frame, text="Перевод: английский → немецкий", font=("Arial", 12))
        language_label.pack(side=tk.LEFT, padx=15)

        text_frame = tk.Frame(self.root)
        text_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        source_frame = tk.LabelFrame(text_frame, text="Исходный текст (английский)", font=("Arial", 12))
        source_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)

        self.text_area = scrolledtext.ScrolledText(source_frame, wrap=tk.WORD, width=40, height=20, font=("Arial", 12))
        self.text_area.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        translated_frame = tk.LabelFrame(text_frame, text="Перевод (немецкий)", font=("Arial", 12))
        translated_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5)

        self.translated_text_area = scrolledtext.ScrolledText(translated_frame, wrap=tk.WORD, width=40, height=20,
                                                              font=("Arial", 12))
        self.translated_text_area.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        analysis_frame = tk.Frame(self.root)
        analysis_frame.pack(fill=tk.X, padx=10, pady=10)

        self.word_count_button = tk.Button(analysis_frame, text="Подсчитать слова", command=self.count_words,
                                           font=("Arial", 12))
        self.word_count_button.pack(side=tk.LEFT, padx=5)

        self.syntax_tree_button = tk.Button(analysis_frame, text="Построить дерево разбора",
                                            command=self.build_syntax_tree, font=("Arial", 12))
        self.syntax_tree_button.pack(side=tk.LEFT, padx=5)

        self.word_freq_button = tk.Button(analysis_frame, text="Частота слов",
                                          command=self.show_word_frequency, font=("Arial", 12))
        self.word_freq_button.pack(side=tk.LEFT, padx=5)

        self.save_dict_button = tk.Button(analysis_frame, text="Сохранить словарь",
                                          command=self.save_word_list, font=("Arial", 12))
        self.save_dict_button.pack(side=tk.LEFT, padx=5)

        self.canvas_frame = tk.Frame(self.root)
        self.canvas_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        self.canvas = tk.Canvas(self.canvas_frame, bg="white")
        self.vertical_scrollbar = tk.Scrollbar(self.canvas_frame, orient="vertical", command=self.canvas.yview)
        self.horizontal_scrollbar = tk.Scrollbar(self.canvas_frame, orient="horizontal", command=self.canvas.xview)

        self.vertical_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.horizontal_scrollbar.pack(side=tk.BOTTOM, fill=tk.X)

        self.canvas.configure(yscrollcommand=self.vertical_scrollbar.set, xscrollcommand=self.horizontal_scrollbar.set)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)


    def open_txt(self):
        file_path = filedialog.askopenfilename(filetypes=[("Text Files", "*.txt")])
        if file_path:
            try:
                with open(file_path, 'r', encoding='utf-8') as file:
                    self.file_content = file.read()

                self.text_area.delete(1.0, tk.END)
                self.text_area.insert(tk.INSERT, self.file_content)

                self.translated_text_area.delete(1.0, tk.END)
                self.translate_button.config(state=tk.NORMAL)
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось открыть TXT: {e}")

    def start_translation_thread(self):
        self.stop_translation_flag = False
        translation_thread = threading.Thread(target=self.translate_text)
        translation_thread.start()
        self.stop_button.config(state=tk.NORMAL)
        self.translate_button.config(state=tk.DISABLED)
        self.open_button.config(state=tk.DISABLED)

    def stop_translation(self):
        self.stop_translation_flag = True
        self.stop_button.config(state=tk.DISABLED)

    def translate_text(self):
        if self.file_content:
            try:
                self.translated_text_area.delete(1.0, tk.END)

                translator = GoogleTranslator(source='en', target='de')

                lines = self.file_content.splitlines()
                for line in lines:
                    if self.stop_translation_flag:
                        break
                    if line.strip():
                        try:
                            translated = translator.translate(line.strip())
                        except Exception as e:
                            translated = f"Ошибка перевода строки: {e}"
                        self.translated_text_area.insert(tk.END, translated + '\n\n')
                        self.translated_text_area.update_idletasks()

                self.translate_button.config(state=tk.NORMAL, text="Перевести")
                self.open_button.config(state=tk.NORMAL)
                self.stop_button.config(state=tk.DISABLED)

            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось перевести текст: {e}")
                self.translate_button.config(state=tk.NORMAL)
                self.stop_button.config(state=tk.DISABLED)
                self.open_button.config(state=tk.NORMAL)
        else:
            messagebox.showwarning("Внимание", "Сначала откройте TXT файл.")


    def count_words(self):
        if self.file_content:
            word_count = len(self.file_content.split())
            messagebox.showinfo("Подсчёт слов", f"Количество слов в тексте: {word_count}")
        else:
            messagebox.showwarning("Внимание", "Сначала откройте TXT файл.")

    def build_syntax_tree(self):
        if self.file_content:
            try:
                doc = nlp(self.file_content)
                all_lines = []

                # рекурсивная функция обхода дерева зависимостей
                def walk(token, level=0):
                    indent = "   " * level
                    lines = [f"{indent}└─ {token.text} ({token.dep_})"]
                    for child in token.children:
                        lines.extend(walk(child, level + 1))
                    return lines

                for sent in doc.sents:
                    root = [token for token in sent if token.head == token]
                    if root:
                        all_lines.append(f"\nПредложение: {sent.text.strip()}\n")
                        all_lines.extend(walk(root[0]))

                tree_text = "\n".join(all_lines)
                self.canvas.delete("all")
                text_id = self.canvas.create_text(
                    10, 10, anchor="nw", text=tree_text,
                    font=("Consolas", 12), fill="black"
                )

                bbox = self.canvas.bbox(text_id)
                if bbox:
                    self.canvas.config(scrollregion=bbox)

            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось построить дерево: {e}")
        else:
            messagebox.showwarning("Внимание", "Сначала откройте TXT файл.")

    def show_word_frequency(self):
        if not self.file_content:
            messagebox.showwarning("Внимание", "Сначала откройте TXT файл.")
            return

        self.word_freq_data = None
        self.translated_text_area.delete(1.0, tk.END)
        self.translated_text_area.insert(tk.END, "Пожалуйста, подождите.\n")

        threading.Thread(target=self._process_word_frequency, daemon=True).start()

    def _process_word_frequency(self):
        try:
            doc = nlp(self.file_content)
            words = [token.text.lower() for token in doc if token.is_alpha]
            freq = Counter(words)

            translator = GoogleTranslator(source='en', target='de')

            word_data = []
            for i, (word, count) in enumerate(freq.most_common(), start=1):
                try:
                    translated = translator.translate(word)
                except Exception:
                    translated = "Ошибка перевода"
                word_data.append((word, count, translated))

                if i % 10 == 0:
                    self.translated_text_area.insert(tk.END, f"Переведено {i} слов...\n")
                    self.translated_text_area.see(tk.END)

            self.word_freq_data = word_data

            result_text = "\n".join([f"{w} — {c} раз(а) — {t}" for w, c, t in word_data])
            self.root.after(0, lambda: self._show_freq_result(result_text))

        except Exception as e:
            self.root.after(0, lambda: messagebox.showerror("Ошибка", f"Ошибка при анализе: {e}"))

    def _show_freq_result(self, text):
        self.translated_text_area.delete(1.0, tk.END)
        self.translated_text_area.insert(tk.END, text)
        messagebox.showinfo("Готово", "Анализ частоты слов завершён!")

    def save_word_list(self):
        if not self.word_freq_data:
            messagebox.showwarning("Внимание", "Сначала нажмите «Частота слов».")
            return

        save_path = filedialog.asksaveasfilename(
            defaultextension=".txt",
            filetypes=[("Text Files", "*.txt")],
            title="Сохранить словарь"
        )

        if save_path:
            try:
                with open(save_path, 'w', encoding='utf-8') as f:
                    for word, count, translation in self.word_freq_data:
                        f.write(f"{word} — {count} — {translation}\n")
                messagebox.showinfo("Успешно", f"Словарь сохранён: {save_path}")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось сохранить файл: {e}")


if __name__ == "__main__":
    root = tk.Tk()
    app = TXTTranslatorApp(root)
    root.mainloop()
