import os
import math
from collections import Counter
from typing import List
import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext

class Document:
    def __init__(self, path: str, text: str):
        self.path = path
        self.text = text
        self.vector = {}

    def tokenize(self):
        tokens = []
        for word in self.text.lower().split():
            clean = ''.join(ch for ch in word if ch.isalnum())
            if clean:
                tokens.append(clean)
        return tokens

    def compute_tf(self): #term frequency
        tokens = self.tokenize()
        counts = Counter(tokens)
        total = len(tokens)
        return {w: c / total for w, c in counts.items()} if total else {}

class Search:
    def __init__(self, documents: List[Document]):
        self.documents = documents
        self.idf = self.compute_idf()
        self.vectorize_documents()

    def compute_idf(self):  #inverse document frequency
        N = len(self.documents)
        df = Counter()
        for doc in self.documents:
            for word in set(doc.tokenize()):
                df[word] += 1
        return {w: math.log10(N / df[w]) for w in df}

    def compute_tf_idf(self, doc: Document):
        tf = doc.compute_tf()
        return {w: tf[w] * self.idf.get(w, 0.0) for w in tf}

    def vectorize_documents(self):
        for doc in self.documents:
            doc.vector = self.compute_tf_idf(doc)

    def vectorize_query(self, query: str):
        tokens = [w.lower() for w in query.split()]
        tf = Counter(tokens)
        total = len(tokens)
        tf = {w: c / total for w, c in tf.items()}
        return {w: tf[w] * self.idf.get(w, 0.0) for w in tf}

    def cosine_similarity(self, v1, v2):
        common = set(v1.keys()) & set(v2.keys())
        num = sum(v1[w] * v2[w] for w in common)
        denom1 = math.sqrt(sum(v ** 2 for v in v1.values()))
        denom2 = math.sqrt(sum(v ** 2 for v in v2.values()))
        return num / (denom1 * denom2) if denom1 and denom2 else 0.0

    def search(self, query: str):
        q_vec = self.vectorize_query(query)
        results = []
        for doc in self.documents:
            sim = self.cosine_similarity(doc.vector, q_vec)
            if sim > 0:
                snippet = doc.text[:250].replace('\n', ' ')
                results.append((doc.path, sim, snippet))
        results.sort(key=lambda x: x[1], reverse=True)
        return results

def load_documents_from_folder(folder: str):
    docs = []
    for root, _, files in os.walk(folder):
        for f in files:
            if f.lower().endswith(".txt"):
                path = os.path.join(root, f)
                with open(path, "r", encoding="utf-8", errors="ignore") as file:
                    text = file.read()
                docs.append(Document(path, text))
    return docs

def run_search():
    query = entry_query.get().strip()
    if not query:
        messagebox.showwarning("Внимание", "Введите поисковый запрос.")
        return

    results = search_engine.search(query)
    text_output.delete(1.0, tk.END)

    if not results:
        text_output.insert(tk.END, "Результатов не найдено.\n")
        return

    for path, sim, snippet in results:
        text_output.insert(tk.END, f"[{sim:.3f}] {os.path.basename(path)}\n{snippet}\n\n")

if __name__ == "__main__":
    folder = filedialog.askdirectory(title="Выберите папку с документами (.txt)")
    if not folder:
        print("Папка не выбрана — завершение программы.")
        exit()

    documents = load_documents_from_folder(folder)
    if not documents:
        print("Нет файлов для индексации в выбранной папке.")
        exit()

    search_engine = Search(documents)

    root = tk.Tk()
    root.geometry("800x600")

    tk.Label(root, text="Введите поисковый запрос:", font=("Arial", 12)).pack(pady=5)
    entry_query = tk.Entry(root, width=80)
    entry_query.pack(pady=5)

    tk.Button(root, text="Поиск", command=run_search, width=15).pack(pady=5)

    text_output = scrolledtext.ScrolledText(root, wrap=tk.WORD, width=90, height=25)
    text_output.pack(padx=10, pady=10)

    root.mainloop()
