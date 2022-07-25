from pkg_resources import to_filename
import serial
import numpy as np
from PIL import Image
import time

class cnc:

    def __init__(self, serial_port, baud=9600, get_ready=True, verbose=True):
        if verbose:
            print("Connecting to CNC...")
        self.serial = serial.Serial(serial_port, baud)
        if get_ready:
            time.sleep(2)
            if verbose:
                print("Ready.")

    def wait(self):
        while True():
            if(self.serial.in_waiting > 0):
                if(self.serial.readline() == b"ready"):
                    return

    def format_int(self, num):
        return str(num).zfill(3)

    def pen_up(self):
        self.wait()
        self.serial.write("4".encode())

    def pen_down(self):
        self.wait()
        self.serial.write("5".encode())

    def move_to(self, x, y):
        self.wait()
        self.serial.write(f"7{self.format_int(x)}{self.format_int(y)}".encode())

    def draw_line(self, start_x, start_y, end_x, end_y):
        self.wait()
        self.serial.write(f"6{self.format_int(start_x)}{self.format_int(start_y)}{self.format_int(end_x)}{self.format_int(end_y)}".encode())
        print(f"6{self.format_int(start_x)}{self.format_int(start_y)}{self.format_int(end_x)}{self.format_int(end_y)}".encode())

    def done(self):
        while True:
            pass

    def draw_image(self, image_path, image_x, image_y):
        """not working ATM"""
        self.wait()
        image = Image.open(image_path)
        image = image.resize((image_x, image_y))
        image = image.convert("1")
        image = np.array(image)
        image = image.flatten()
        image = image.tolist()
        image = list(map(int, image))
        image = "".join(list(map(str, image)))
        image = self.format_int(image_x) + self.format_int(image_y) + image
        #print(f"8{image}".encode())
        self.serial.write(f"8{image}".encode())
