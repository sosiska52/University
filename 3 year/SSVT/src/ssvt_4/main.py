import tkinter as tk
import math


class BouncingBall:
    def __init__(self, root):
        self.root = root
        self.root.title("Шарик с гравитацией")

        self.width = 400
        self.height = 400
        self.radius = 150
        self.ball_radius = 15

        self.canvas = tk.Canvas(root, width=self.width, height=self.height, bg="white")
        self.canvas.pack()

        self.circle = self.canvas.create_oval(
            self.width // 2 - self.radius,
            self.height // 2 - self.radius,
            self.width // 2 + self.radius,
            self.height // 2 + self.radius,
            outline="black",
            width=2
        )

        self.ball_x = self.width // 2
        self.ball_y = self.height // 2 - 100
        self.ball_dx = 2
        self.ball_dy = 0
        self.gravity = 0.2

        self.ball = self.canvas.create_oval(
            self.ball_x - self.ball_radius,
            self.ball_y - self.ball_radius,
            self.ball_x + self.ball_radius,
            self.ball_y + self.ball_radius,
            fill="red",
            outline="black"
        )

        self.root.after(10, self.update_ball)

    def update_ball(self):
        self.ball_dy += self.gravity
        self.ball_x += self.ball_dx
        self.ball_y += self.ball_dy

        distance_from_center = math.sqrt(
            (self.ball_x - self.width // 2) ** 2 +
            (self.ball_y - self.height // 2) ** 2
        )

        if distance_from_center + self.ball_radius > self.radius:
            nx = (self.ball_x - self.width // 2) / distance_from_center
            ny = (self.ball_y - self.height // 2) / distance_from_center

            dot_product = self.ball_dx * nx + self.ball_dy * ny

            self.ball_dx -= 2 * dot_product * nx * 0.95
            self.ball_dy -= 2 * dot_product * ny * 0.95

            correction = (distance_from_center + self.ball_radius - self.radius) + 1
            self.ball_x -= correction * nx
            self.ball_y -= correction * ny

        self.canvas.coords(
            self.ball,
            self.ball_x - self.ball_radius,
            self.ball_y - self.ball_radius,
            self.ball_x + self.ball_radius,
            self.ball_y + self.ball_radius
        )

        self.root.after(10, self.update_ball)


if __name__ == "__main__":
    root = tk.Tk()
    app = BouncingBall(root)
    root.mainloop()