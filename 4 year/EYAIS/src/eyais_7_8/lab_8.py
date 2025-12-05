import tkinter as tk
from tkinter import ttk
import pyttsx3
import threading

class TTSApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Лаб8")

        temp_engine = pyttsx3.init()
        self.voices = temp_engine.getProperty('voices')
        del temp_engine

        self.voice_label = tk.Label(root, text="Выберите голос:", font=("Arial", 12))
        self.voice_label.pack(pady=5)

        self.voice_var = tk.StringVar(value=self.voices[0].name)
        self.voice_combobox = ttk.Combobox(
            root, textvariable=self.voice_var,
            values=[voice.name for voice in self.voices],
            state="readonly", width=40
        )
        self.voice_combobox.pack(pady=5)

        self.speed_label = tk.Label(root, text="Установите скорость:", font=("Arial", 12))
        self.speed_label.pack(pady=5)

        self.speed_scale = tk.Scale(root, from_=50, to=300, orient=tk.HORIZONTAL,
                                    label="Скорость (слов в минуту)", length=400)
        self.speed_scale.set(150)
        self.speed_scale.pack(pady=5)

        self.volume_label = tk.Label(root, text="Установите громкость:", font=("Arial", 12))
        self.volume_label.pack(pady=5)

        self.volume_scale = tk.Scale(root, from_=0.0, to=1.0,
                                     resolution=0.1,
                                     orient=tk.HORIZONTAL,
                                     label="Громкость",
                                     length=400)
        self.volume_scale.set(1.0)
        self.volume_scale.pack(pady=5)

        self.label = tk.Label(root, text="Введите текст:", font=("Arial", 16))
        self.label.pack(pady=10)

        self.text_entry = tk.Text(root, height=10, width=50)
        self.text_entry.pack(pady=10)

        self.speak_button = tk.Button(
            root, text="ПРОИЗНЕСИТЬ",
            command=self.start_speech_thread,
            font=("Arial", 12)
        )
        self.speak_button.pack(pady=10)

    def start_speech_thread(self):
        threading.Thread(target=self.speak_text, daemon=True).start()

    def speak_text(self):
        text = self.text_entry.get("1.0", tk.END).strip()

        engine = pyttsx3.init()

        engine.setProperty('voice', self.get_selected_voice_id())
        engine.setProperty('rate', self.speed_scale.get())
        engine.setProperty('volume', self.volume_scale.get())

        engine.say(text)
        engine.runAndWait()

        engine.stop()
        del engine

    def get_selected_voice_id(self):
        selected = self.voice_var.get()
        for voice in self.voices:
            if voice.name == selected:
                return voice.id
        return self.voices[0].id


if __name__ == '__main__':
    root = tk.Tk()
    app = TTSApp(root)
    root.mainloop()
