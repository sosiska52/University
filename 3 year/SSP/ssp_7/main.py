import tkinter as tk
from tkinter import simpledialog
import threading
import time
import math
import winsound

class ClockApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Механические часы с будильником")
        self.root.geometry("400x450")

        self.alarm_hour = 0
        self.alarm_minute = 0
        self.alarm_second = 0
        self.alarm_active = False

        self.canvas = tk.Canvas(root, width=400, height=400, bg="white")
        self.canvas.pack()

        self.alarm_button = tk.Button(root, text="Установить будильник", command=self.set_alarm)
        self.alarm_button.pack()

        self.draw_clock_face()

        self.clock_thread = threading.Thread(target=self.update_clock, daemon=True)
        self.clock_thread.start()

        self.alarm_thread = threading.Thread(target=self.check_alarm, daemon=True)
        self.alarm_thread.start()

    def draw_clock_face(self):
        self.canvas.create_oval(50, 50, 350, 350, width=2)
        for i in range(12):
            angle = math.radians(90 - i * 30)
            x = 200 + 130 * math.cos(angle)
            y = 200 - 130 * math.sin(angle)
            self.canvas.create_text(x, y, text=str(12 if i == 0 else i), font=("Arial", 12))

    def draw_hands(self, hour, minute, second):
        self.canvas.delete("hand")

        angle = math.radians(90 - second * 6)
        x = 200 + 120 * math.cos(angle)
        y = 200 - 120 * math.sin(angle)
        self.canvas.create_line(200, 200, x, y, fill="red", width=1, tag="hand")

        angle = math.radians(90 - minute * 6)
        x = 200 + 100 * math.cos(angle)
        y = 200 - 100 * math.sin(angle)
        self.canvas.create_line(200, 200, x, y, fill="blue", width=2, tag="hand")

        angle = math.radians(90 - (hour % 12) * 30 - minute * 0.5)
        x = 200 + 70 * math.cos(angle)
        y = 200 - 70 * math.sin(angle)
        self.canvas.create_line(200, 200, x, y, fill="black", width=4, tag="hand")

    def update_clock(self):
        while True:
            now = time.localtime()
            hour = now.tm_hour
            minute = now.tm_min
            second = now.tm_sec

            self.draw_hands(hour, minute, second)

            time.sleep(1)

    def set_alarm(self):
        alarm_time = simpledialog.askstring("Установка будильника", "Введите время в формате ЧЧ:ММ:СС")
        if alarm_time:
            self.alarm_hour, self.alarm_minute, self.alarm_second = map(int, alarm_time.split(":"))
            self.alarm_active = True

    def check_alarm(self):
        while True:
            if self.alarm_active:
                now = time.localtime()
                if (now.tm_hour == self.alarm_hour and
                    now.tm_min == self.alarm_minute and
                    now.tm_sec == self.alarm_second):
                    self.trigger_alarm()
                    self.alarm_active = False
            time.sleep(1)

    def trigger_alarm(self):
        winsound.Beep(1000, 500)

if __name__ == "__main__":
    root = tk.Tk()
    app = ClockApp(root)
    root.mainloop()