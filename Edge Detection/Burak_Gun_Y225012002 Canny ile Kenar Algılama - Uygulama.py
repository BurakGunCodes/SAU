import cv2
from tkinter import *
from tkinter import filedialog
from PIL import Image, ImageTk

class App:
    def __init__(self, window, window_title):
        self.window = window
        self.window.title(window_title)
        self.vid = cv2.VideoCapture(0)

        
        self.canvas = Canvas(window, width=1200, height=600)
        self.canvas.pack()

        self.btn_open_camera = Button(window, text="Kamera Aç", width=10, command=self.toggle_camera)
        self.btn_open_camera.pack(side="bottom", fill="both", expand="yes", padx=10, pady=10)

        self.btn_find_edges = Button(window, text="Kenar Bul", width=10, command=self.find_edges)
        self.btn_find_edges.pack(side="bottom", fill="both", expand="yes", padx=10, pady=10)

        self.btn_select_image = Button(window, text="Resim Ekle", width=10, command=self.select_image)
        self.btn_select_image.pack(side="bottom", fill="both", expand="yes", padx=10, pady=10)


        self.image_panel = None
        self.edges_panel = None

        self.running = False
        self.original_image = None  

        self.window.mainloop()

    def toggle_camera(self):
        if not self.running:
            self.running = True
            self.btn_open_camera.config(text="Kamera Kapat")
            self.update_camera()
        else:
            self.running = False
            self.btn_open_camera.config(text="Video Aç")
            self.clear_panels()

    def update_camera(self):
        if self.running:
            ret, frame = self.vid.read()
            if ret:
                self.display_image(frame, "left")
                edges = cv2.Canny(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY), 50, 150)
                self.display_image(edges, "right")
            self.window.after(10, self.update_camera)

    def select_image(self):
        self.image_path = filedialog.askopenfilename()
        if self.image_path:
            image = cv2.imread(self.image_path, cv2.IMREAD_COLOR)
            if image is not None:
                self.original_image = image
                self.display_image(self.resize_image(image), "left")
            
            if self.edges_panel:
                self.canvas.delete(self.edges_panel)
                self.edges_panel = None

    def find_edges(self):
        if self.original_image is not None:
            gray = cv2.cvtColor(self.original_image, cv2.COLOR_BGR2GRAY)
            blurred = cv2.GaussianBlur(gray, (5, 5), 0)
            edges = cv2.Canny(blurred, 50, 150)
            self.display_image(self.resize_image(edges), "right")

    def display_image(self, img, position):
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) if position == "left" else img
        img = Image.fromarray(img)
        imgtk = ImageTk.PhotoImage(image=img)
        if position == "left":
            if self.image_panel:
                self.canvas.delete(self.image_panel)
            self.image_panel = self.canvas.create_image(0, 0, anchor=NW, image=imgtk)
        else:
            if self.edges_panel:
                self.canvas.delete(self.edges_panel)
            self.edges_panel = self.canvas.create_image(600, 0, anchor=NW, image=imgtk)
        if position == "left":
            self.canvas.image = imgtk
        else:
            self.canvas.edges_image = imgtk

    def resize_image(self, image, max_size=500):
        height, width = image.shape[:2]
        scaling_factor = max_size / max(height, width)
        return cv2.resize(image, None, fx=scaling_factor, fy=scaling_factor, interpolation=cv2.INTER_LINEAR)

    def clear_panels(self):
        if self.image_panel:
            self.canvas.delete(self.image_panel)
            self.image_panel = None
        if self.edges_panel:
            self.canvas.delete(self.edges_panel)
            self.edges_panel = None

    def __del__(self):
        if self.vid.isOpened():
            self.vid.release()

if __name__ == "__main__":
    root = Tk()
    app = App(root, "Video ve Resim Üzerinde Kenar Algılama Uygulaması")
