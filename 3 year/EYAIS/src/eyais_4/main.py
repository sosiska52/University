import tkinter as tk
from tkinter import filedialog
import docx2txt
from natasha import (
    Segmenter,
    MorphVocab,
    NewsEmbedding,
    NewsMorphTagger,
    NewsSyntaxParser,
    NewsNERTagger,
    Doc
)
from transformers import pipeline
import torch

segmenter = Segmenter()
morph_vocab = MorphVocab()
emb = NewsEmbedding()
morph_tagger = NewsMorphTagger(emb)
syntax_parser = NewsSyntaxParser(emb)
ner_tagger = NewsNERTagger(emb)

sentiment_analyzer = pipeline(
    "sentiment-analysis",
    model="blanchefort/rubert-base-cased-sentiment",
    tokenizer="blanchefort/rubert-base-cased-sentiment"
)

subjectivity_analyzer = pipeline(
    "text-classification",
    model="cointegrated/rubert-tiny2-cedr-emotion-detection"
)


def translate_sentiment(label):
    translations = {
        "POSITIVE": "Позитивный",
        "NEUTRAL": "Нейтральный",
        "NEGATIVE": "Негативный"
    }
    return translations.get(label, label)


def translate_subjectivity(label):
    return "Субъективный" if label == "SUBJ" else "Объективный"


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
    return {translations.get(k, k): v for k, v in feats.items()}


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


def analyze_semantics(text):
    sentiment = sentiment_analyzer(text[:512], truncation=True)[0]
    subjectivity = subjectivity_analyzer(text[:512], truncation=True)[0]

    return {
        "sentiment": f"{translate_sentiment(sentiment['label'])} ({sentiment['score']:.2f})",
        "subjectivity": f"{translate_subjectivity(subjectivity['label'])} ({subjectivity['score']:.2f})"
    }


def analyze_text(text):
    doc = Doc(text)
    doc.segment(segmenter)
    doc.tag_morph(morph_tagger)
    doc.parse_syntax(syntax_parser)
    doc.tag_ner(ner_tagger)

    result = []

    semantic_result = analyze_semantics(text)
    result.append("=== Семантический анализ всего текста ===")
    result.append(f"Эмоциональная окраска: {semantic_result['sentiment']}")
    result.append(f"Субъективность/Объективность: {semantic_result['subjectivity']}")
    result.append("\n")

    for sent in doc.sents:
        result.append(f"=== Предложение: {sent.text} ===")

        entities = [f"{span.text} ({span.type})" for span in sent.spans]
        if entities:
            result.append("Именованные сущности: " + ", ".join(entities))

        result.append("Синтаксический анализ:")
        for token in sent.tokens:
            if token.pos == 'PUNCT':
                continue

            translated_feats = translate_feats(token.feats)
            translated_rel = translate_rel(token.rel)

            token_info = (
                f"Слово: {token.text}\n"
                f"Лемма: {token.lemma or 'неизвестно'}\n"
                f"Часть речи: {token.pos}\n"
                f"Грамм. признаки: {translated_feats}\n"
                f"Синт. связь: {translated_rel}\n"
            )
            result.append(token_info)

        sent_semantic = analyze_semantics(sent.text)
        result.append("Семантический анализ предложения:")
        result.append(f"- Эмоциональная окраска: {sent_semantic['sentiment']}")
        result.append(f"- Субъективность: {sent_semantic['subjectivity']}")
        result.append("\n")

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
root.title("Расширенный семантико-синтаксический анализатор")
root.geometry("1200x900")

load_button = tk.Button(root, text="Загрузить файл", command=load_file)
load_button.pack(pady=10)

original_label = tk.Label(root, text="Оригинальный текст:")
original_label.pack()
original_text = tk.Text(root, height=12, wrap=tk.WORD)
original_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

result_label = tk.Label(root, text="Результат анализа:")
result_label.pack()
result_text = tk.Text(root, height=35, wrap=tk.WORD)
result_text.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

root.mainloop()