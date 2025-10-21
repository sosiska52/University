import re
import nltk
import tkinter as tk
from tkinter import filedialog, Text, ttk
from sklearn.feature_extraction.text import TfidfVectorizer
from transformers import T5ForConditionalGeneration, T5Tokenizer
import threading
import PyPDF2

nltk.download('punkt', quiet=True)
nltk.download('stopwords', quiet=True)

from nltk.corpus import stopwords
from nltk.tokenize import sent_tokenize, word_tokenize

ml_model = None
ml_tokenizer = None
ml_loaded = False

def load_ml_model():
    global ml_model, ml_tokenizer, ml_loaded
    try:
        model_name = "t5-small"
        ml_model = T5ForConditionalGeneration.from_pretrained(model_name)
        ml_tokenizer = T5Tokenizer.from_pretrained(model_name)
        ml_loaded = True
    except Exception as e:
        print(f"Error loading ML model: {e}")
        ml_loaded = False

load_ml_model()

def extract_text_from_pdf(pdf_file):
    text = ""
    try:
        with open(pdf_file, 'rb') as file:
            reader = PyPDF2.PdfReader(file)
            for page in reader.pages:
                page_text = page.extract_text()
                if page_text:
                    text += page_text + "\n"  # добавляем текст каждой страницы
    except Exception as e:
        print(f"Error reading PDF: {e}")
    return text

def clean_text(text):
    text = re.sub(r'\s+', ' ', text)  # заменяем все пробельные символы на один пробел
    text = re.sub(r'\d+', '', text)   # удаляем цифры
    return text

def extract_sentences_tfidf(text, language='spanish'):
    sentences = sent_tokenize(text)  # разбиваем текст на предложения

    if not sentences:
        return [], []

    try:
        stop_words = set(stopwords.words(language))
    except:
        stop_words = set(stopwords.words('english'))  # на случай ошибки используем английский

    cleaned_sentences = [' '.join([word for word in word_tokenize(sentence.lower())
                                   if word.isalpha() and word not in stop_words])
                         for sentence in sentences]

    vectorizer = TfidfVectorizer()
    tfidf_matrix = vectorizer.fit_transform(cleaned_sentences)  # считаем TF-IDF

    return sentences, tfidf_matrix.sum(axis=1).A1  # возвращаем предложения и их веса

def generate_summary(sentences, sentence_weights, summary_length=5):
    if not sentences:
        return "No text available for summarization."

    # сортируем предложения по весу
    ranked_sentences = sorted(((weight, sentence) for sentence, weight in zip(sentences, sentence_weights)),
                              reverse=True)
    summary_length = min(summary_length, len(ranked_sentences))  # чтобы не выйти за предел
    summary = ' '.join([sentence for weight, sentence in ranked_sentences[:summary_length]])
    return summary

def generate_ml_summary(text):
    if not ml_loaded:
        return "ML model not available. Please check console for errors."

    try:
        input_text = "summarize: " + text
        inputs = ml_tokenizer(input_text, return_tensors="pt", max_length=512, truncation=True)

        summary_ids = ml_model.generate(
            inputs["input_ids"],
            max_length=100,
            min_length=30,
            length_penalty=2.0,
            early_stopping=True
        )

        summary = ml_tokenizer.decode(summary_ids[0], skip_special_tokens=True)
        return summary
    except Exception as e:
        return f"Error generating ML summary: {str(e)}"

def summarize_pdf(pdf_file, method, language='spanish'):
    text = extract_text_from_pdf(pdf_file)  # получаем текст

    if not text.strip():
        return "No text extracted from PDF", "Cannot summarize empty text"

    cleaned_text = clean_text(text)

    if method == "TF-IDF":
        sentences, sentence_weights = extract_sentences_tfidf(cleaned_text, language)
        summary = generate_summary(sentences, sentence_weights)
    elif method == "ML":
        summary = generate_ml_summary(cleaned_text)
    else:
        summary = "Unknown method"

    return text, summary

def open_file():
    filepath = filedialog.askopenfilename(filetypes=[("PDF files", "*.pdf")])
    if filepath:
        selected_file.set(filepath)
        original_text_box.delete(1.0, tk.END)
        original_text_box.insert(tk.END, "Текст...")
        threading.Thread(target=extract_and_display_text, args=(filepath,)).start()

def extract_and_display_text(filepath):
    text = extract_text_from_pdf(filepath)
    original_text_box.delete(1.0, tk.END)
    original_text_box.insert(tk.END, text)

def run_summarize():
    if not selected_file.get():
        summary_text_box.delete(1.0, tk.END)
        summary_text_box.insert(tk.END, "Выберите PDF")
        return

    summary_text_box.delete(1.0, tk.END)
    summary_text_box.insert(tk.END, "Генерация резюме...")

    root.update()

    threading.Thread(target=summarize).start()

def summarize():
    try:
        method_choice = method.get()         # какой метод выбрали
        language_choice = language_var.get() # какой язык

        original_text, summary = summarize_pdf(selected_file.get(), method_choice, language_choice)

        root.after(0, update_results, original_text, summary)  # обновляем интерфейс безопасно из потока

    except Exception as e:
        root.after(0, show_error, str(e))

def update_results(original_text, summary):
    original_text_box.delete(1.0, tk.END)
    original_text_box.insert(tk.END, original_text)

    summary_text_box.delete(1.0, tk.END)
    summary_text_box.insert(tk.END, summary)

def show_error(error_msg):
    summary_text_box.delete(1.0, tk.END)
    summary_text_box.insert(tk.END, f"Error: {error_msg}")

root = tk.Tk()
root.title("Резюме")
root.geometry("800x700")

selected_file = tk.StringVar()
method = tk.StringVar(value="TF-IDF")
language_var = tk.StringVar(value="spanish")

file_button = tk.Button(root, text="Выбор PDF", command=open_file)
file_button.pack(pady=10)

file_label = tk.Label(root, textvariable=selected_file)
file_label.pack()

language_label = tk.Label(root, text="Выбор языка")
language_label.pack()

spanish_radio = tk.Radiobutton(root, text="Español", variable=language_var, value="spanish")
spanish_radio.pack(anchor="w")

italian_radio = tk.Radiobutton(root, text="Italiano", variable=language_var, value="italian")
italian_radio.pack(anchor="w")

method_label = tk.Label(root, text="Метод")
method_label.pack()

tfidf_radio = tk.Radiobutton(root, text="TF-IDF", variable=method, value="TF-IDF")
tfidf_radio.pack(anchor="w")

ml_radio = tk.Radiobutton(root, text="ML", variable=method, value="ML")
ml_radio.pack(anchor="w")

summarize_button = tk.Button(root, text="Генерация резюме", command=run_summarize)
summarize_button.pack(pady=10)

notebook = ttk.Notebook(root)
notebook.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

original_frame = ttk.Frame(notebook)
notebook.add(original_frame, text="Оригинальный текст")

original_text_label = tk.Label(original_frame, text="Оригинальный текст")
original_text_label.pack(anchor="w")

original_text_box = Text(original_frame, height=12, width=80)
original_scrollbar = tk.Scrollbar(original_frame, command=original_text_box.yview)
original_text_box.configure(yscrollcommand=original_scrollbar.set)
original_text_box.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
original_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

summary_frame = ttk.Frame(notebook)
notebook.add(summary_frame, text="Резюме")

summary_text_label = tk.Label(summary_frame, text="Резюме:")
summary_text_label.pack(anchor="w")

summary_text_box = Text(summary_frame, height=12, width=80)
summary_scrollbar = tk.Scrollbar(summary_frame, command=summary_text_box.yview)
summary_text_box.configure(yscrollcommand=summary_scrollbar.set)
summary_text_box.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
summary_scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

root.mainloop()