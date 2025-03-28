import tkinter as tk
from enum import Enum


class TrafficLightState(Enum):
    RED = 1
    YELLOW = 2
    GREEN = 3


class PedestrianLightState(Enum):
    RED = 1
    GREEN = 2


class TrafficLightSimulator:
    def __init__(self, root):
        self.root = root
        self.root.title("Управление светофорами")

        self.traffic_light_state = TrafficLightState.GREEN
        self.pedestrian_light_state = PedestrianLightState.RED
        self.button_pressed = False
        self.button_cooldown = False
        self.current_timer = 0
        self.stage_name = ""

        self.canvas = tk.Canvas(root, width=400, height=400, bg='white')
        self.canvas.pack(pady=10)

        self.canvas.create_rectangle(50, 50, 150, 250, fill='gray', outline='black')
        self.traffic_red = self.canvas.create_oval(60, 60, 140, 140, fill='black', outline='black')
        self.traffic_yellow = self.canvas.create_oval(60, 150, 140, 190, fill='black', outline='black')
        self.traffic_green = self.canvas.create_oval(60, 200, 140, 240, fill='green', outline='black')

        self.canvas.create_rectangle(250, 50, 350, 200, fill='gray', outline='black')
        self.ped_red = self.canvas.create_oval(260, 60, 340, 120, fill='red', outline='black')
        self.ped_green = self.canvas.create_oval(260, 130, 340, 190, fill='black', outline='black')

        self.button = tk.Button(root, text="Нажать для перехода", command=self.press_button)
        self.button.pack(pady=5)

        self.status_label = tk.Label(root, text="Светофоры работают в автоматическом режиме")
        self.status_label.pack()

        self.timer_label = tk.Label(root, text="", font=('Arial', 12))
        self.timer_label.pack()

        self.update_lights()
        self.start_normal_cycle()
        self.update_timer()

    def press_button(self):
        if not self.button_pressed and not self.button_cooldown and self.traffic_light_state == TrafficLightState.GREEN:
            self.button_pressed = True
            self.button_cooldown = True
            self.status_label.config(text="Запрос на переход получен, ожидайте зеленый свет")
            if hasattr(self, 'normal_cycle_timer'):
                self.root.after_cancel(self.normal_cycle_timer)
            self.begin_transition()

    def update_lights(self):
        self.canvas.itemconfig(self.traffic_red,
                               fill='red' if self.traffic_light_state == TrafficLightState.RED else 'black')
        self.canvas.itemconfig(self.traffic_yellow,
                               fill='yellow' if self.traffic_light_state == TrafficLightState.YELLOW else 'black')
        self.canvas.itemconfig(self.traffic_green,
                               fill='green' if self.traffic_light_state == TrafficLightState.GREEN else 'black')

        self.canvas.itemconfig(self.ped_red,
                               fill='red' if self.pedestrian_light_state == PedestrianLightState.RED else 'black')
        self.canvas.itemconfig(self.ped_green,
                               fill='green' if self.pedestrian_light_state == PedestrianLightState.GREEN else 'black')

    def update_timer(self):
        if self.current_timer > 0:
            self.timer_label.config(text=f"{self.current_timer} сек. {self.stage_name}")
            self.current_timer -= 1
            self.root.after(1000, self.update_timer)
        else:
            self.timer_label.config(text="")

    def start_normal_cycle(self):
        self.traffic_light_state = TrafficLightState.GREEN
        self.pedestrian_light_state = PedestrianLightState.RED
        self.button_pressed = False
        self.update_lights()
        self.status_label.config(text="Светофоры работают в автоматическом режиме")
        self.current_timer = 25
        self.stage_name = "до разблокировки кнопки"
        self.update_timer()
        self.normal_cycle_timer = self.root.after(25000, lambda: setattr(self, 'button_cooldown', False))

    def begin_transition(self):
        self.traffic_light_state = TrafficLightState.YELLOW
        self.update_lights()
        self.current_timer = 3
        self.stage_name = "желтого цвета"
        self.update_timer()
        self.root.after(3000, self.complete_transition)

    def complete_transition(self):
        self.traffic_light_state = TrafficLightState.RED
        self.pedestrian_light_state = PedestrianLightState.GREEN
        self.update_lights()
        self.status_label.config(text="Переход разрешен")
        self.current_timer = 16
        self.stage_name = "зеленого для пешеходов"
        self.update_timer()
        self.root.after(16000, self.prepare_return_to_normal)

    def prepare_return_to_normal(self):
        self.pedestrian_light_state = PedestrianLightState.RED
        self.update_lights()
        self.current_timer = 3
        self.stage_name = "красного для всех"
        self.update_timer()
        self.root.after(3000, self.return_to_normal_yellow)

    def return_to_normal_yellow(self):
        self.traffic_light_state = TrafficLightState.YELLOW
        self.update_lights()
        self.current_timer = 3
        self.stage_name = "желтого перед зеленым"
        self.update_timer()
        self.root.after(3000, self.finish_return_to_normal)

    def finish_return_to_normal(self):
        self.start_normal_cycle()


if __name__ == "__main__":
    root = tk.Tk()
    app = TrafficLightSimulator(root)
    root.mainloop()