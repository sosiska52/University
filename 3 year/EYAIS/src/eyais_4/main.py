import tkinter as tk
from tkinter import filedialog
import docx2txt
from natasha import (
    Segmenter,
    MorphVocab,
    NewsEmbedding,
    NewsMorphTagger,
    NewsSyntaxParser,
    Doc
)

segmenter = Segmenter()
morph_vocab = MorphVocab()
emb = NewsEmbedding()
morph_tagger = NewsMorphTagger(emb)
syntax_parser = NewsSyntaxParser(emb)


def translate_feats(feats):
    translations = {
        "Animacy": "Одушевленность",
        "Case": "Падеж",
        "Gender": "Род",
        "Number": "Число",
        "Aspect": "Вид",
        "Mood": "Наклонение",
        "Tense": "Время",
        "VerbForm": "Форма глагола",
        "Voice": "Залог",
        "Degree": "Степень",
        "Person": "Лицо",
    }
    translated_feats = {}
    for key, value in feats.items():
        translated_key = translations.get(key, key)
        translated_feats[translated_key] = value
    return translated_feats


def translate_rel(rel):
    rel_translations = {
        "root": "корень",
        "nsubj": "подлежащее",
        "obj": "дополнение",
        "nmod": "именная модификация",
        "advmod": "наречное модифицирующее слово",
        "punct": "знак препинания",
    }
    return rel_translations.get(rel, rel)


def analyze_text(text):
    doc = Doc(text)
    doc.segment(segmenter)
    doc.tag_morph(morph_tagger)
    doc.parse_syntax(syntax_parser)

    result = []
    for sent in doc.sents:
        result.append(f"Предложение: {sent.text}")
        for token in sent.tokens:
            translated_feats = translate_feats(token.feats)
            translated_rel = translate_rel(token.rel)

            token_info = (
                f"Слово: {token.text}\n"
                f"Лемма: {token.lemma if token.lemma else 'неизвестно'}\n"
                f"Часть речи: {token.pos}\n"
                f"Грамматические признаки: {translated_feats}\n"
                f"Главное слово (ID): {token.head_id}\n"
                f"Синтаксическая связь: {translated_rel}\n"
            )
            result.append(token_info)
        result.append("")
    return "\n".join(result)


def load_file():
    file_path = filedialog.askopenfilename(
        title="Выберите файл Word",
        filetypes=[("Word files", "*.docx")]
    )
    if not file_path:
        return

    text = docx2txt.process(file_path)

    original_text.delete(1.0, tk.END)
    original_text.insert(tk.END, text)

    analysis_result = analyze_text(text)

    result_text.delete(1.0, tk.END)
    result_text.insert(tk.END, analysis_result)


root = tk.Tk()
root.title("Синтаксический анализатор текста")
root.geometry("800x600")

load_button = tk.Button(root, text="Загрузить файл", command=load_file)
load_button.pack(pady=10)

original_label = tk.Label(root, text="Оригинальный текст:")
original_label.pack()
original_text = tk.Text(root, height=10, wrap=tk.WORD)
original_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

result_label = tk.Label(root, text="Результат синтаксического разбора:")
result_label.pack()
result_text = tk.Text(root, height=20, wrap=tk.WORD)
result_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

root.mainloop()