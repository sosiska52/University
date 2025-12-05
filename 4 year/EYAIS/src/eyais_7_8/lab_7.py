import tkinter as tk
import sounddevice as sd
import soundfile as sf
import speech_recognition as sr
import threading


class SpeechApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Лаб7")

        self.label = tk.Label(root, text="Нажмите кнопку и говорите:", font=("Arial", 16))
        self.label.pack(pady=20)

        self.result_text = tk.Text(root, height=10, width=50)
        self.result_text.pack(pady=20)

        self.recognize_button = tk.Button(root, text="Распознать речь",
                                          command=self.start_recognition_thread,
                                          font=("Arial", 12))
        self.recognize_button.pack(pady=20)

    def start_recognition_thread(self):
        threading.Thread(target=self.recognize_speech).start()

    def recognize_speech(self):
        self.label.config(text="Слушаю... (3 сек)")

        SAMPLE_RATE = 16000
        RECORD_SECONDS = 3
        FILE_NAME = "temp.wav"

        try:
            audio = sd.rec(int(RECORD_SECONDS * SAMPLE_RATE),
                           samplerate=SAMPLE_RATE,
                           channels=1,
                           dtype='int16')

            sd.wait()

            sf.write(FILE_NAME, audio, SAMPLE_RATE)

        except Exception as e:
            self.label.config(text=f"Ошибка записи: {e}")
            return

        self.label.config(text="Обрабатываю...")

        recognizer = sr.Recognizer()

        try:
            with sr.AudioFile(FILE_NAME) as source:
                audio_data = recognizer.record(source)

            text = recognizer.recognize_google(audio_data, language="ru-RU")

            self.result_text.delete(1.0, tk.END)
            self.result_text.insert(tk.END, text)

            self.label.config(text="Нажмите кнопку и говорите:")

        except sr.UnknownValueError:
            self.label.config(text="Не удалось распознать речь.")
        except sr.RequestError as e:
            self.label.config(text=f"Ошибка сервиса: {e}")
        except Exception as e:
            self.label.config(text=f"Ошибка: {e}")

if __name__ == '__main__':
    root = tk.Tk()
    app = SpeechApp(root)
    root.mainloop()
