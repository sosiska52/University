from PIL import Image, ImageDraw
import random

def add_noise(image_path, noise_level=100):
    img = Image.open(image_path)
    draw = ImageDraw.Draw(img)

    width, height = img.size

    for _ in range(noise_level):
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        draw.point((x, y), fill=(255, 255, 255))

    """for _ in range(noise_level // 10):
        x1 = random.randint(0, width - 1)
        y1 = random.randint(0, height - 1)
        x2 = random.randint(0, width - 1)
        y2 = random.randint(0, height - 1)
        draw.line((x1, y1, x2, y2), fill=(255, 255, 255), width=1)"""

    img.save("corrupted_" + image_path)
    img.show()

def denoise(image_path):
    pass