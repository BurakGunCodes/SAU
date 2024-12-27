import cv2
from tkinter import *
from tkinter import filedialog
from PIL import Image, ImageTk
import numpy as np
from tensorflow.keras.models import load_model

# Modeli yükle
model = load_model('mnist_digit_recognizer.h5')

class Uygulama:

    def __init__(self, pencere, pencere_basligi):
        self.pencere = pencere
        self.pencere.title(pencere_basligi)
        

        self.cizim_alani = Canvas(pencere, width=1200, height=600)
        self.cizim_alani.pack()

        self.btn_tahmin_et = Button(pencere, text="Tahmin", width=10, command=self.tahmin_et)
        self.btn_tahmin_et.pack(side="bottom", fill="both", expand="yes", padx=10, pady=10)

        self.btn_resim_ekle = Button(pencere, text="Resim Ekle", width=10, command=self.resim_sec)
        self.btn_resim_ekle.pack(side="bottom", fill="both", expand="yes", padx=10, pady=10)

        self.resim_alani = None
        self.tahmin_sonuc_etiketi = None

        self.orijinal_resim = None
        self.resim_yolu = None

        self.pencere.mainloop()

    def resmi_on_isle(self, resim_yolu):
        resim = cv2.imread(resim_yolu, cv2.IMREAD_GRAYSCALE)

        if resim is None:
            raise ValueError("Görüntü yüklenemedi. Lütfen dosya yolunu kontrol edin.")
    
        resim = cv2.resize(resim, (28, 28))
        resim = resim / 255.0
        resim = resim.reshape(1, 28, 28, 1)
    
        return resim

    def resim_sec(self):
        self.resim_yolu = filedialog.askopenfilename(initialdir="/", title="Resim Seç", filetypes=(("PNG files", "*.png"), ("JPEG files", "*.jpg"), ("All files", "*.*")))
        print(self.resim_yolu)
        
        if self.resim_yolu:
            resim = cv2.imread(self.resim_yolu, cv2.IMREAD_COLOR)
            if resim is not None:
                self.orijinal_resim = resim
                self.resim_goster(self.resmi_boyutlandir(resim), "left")
            
            if self.tahmin_sonuc_etiketi:
                self.cizim_alani.delete(self.tahmin_sonuc_etiketi)
                self.tahmin_sonuc_etiketi = None

    def tahmin_et(self):
        resim = self.resmi_on_isle(self.resim_yolu)
        tahmin = model.predict(resim)
        tahmin_edilen_sayi = np.argmax(tahmin)
        print("Tahmin Edilen Sayı:", tahmin_edilen_sayi)

        if self.tahmin_sonuc_etiketi:
            self.cizim_alani.delete(self.tahmin_sonuc_etiketi)
        
        self.tahmin_sonuc_etiketi = self.cizim_alani.create_text(900, 300, text=f"Tahmin Edilen Sayı: {tahmin_edilen_sayi}", font=("Helvetica", 24), fill="black")

    def resim_goster(self, resim, konum):
        resim = cv2.cvtColor(resim, cv2.COLOR_BGR2RGB) if konum == "left" else resim
        resim = Image.fromarray(resim)
        resimtk = ImageTk.PhotoImage(image=resim)
        if konum == "left":
            if self.resim_alani:
                self.cizim_alani.delete(self.resim_alani)
            self.resim_alani = self.cizim_alani.create_image(0, 0, anchor=NW, image=resimtk)
        if konum == "left":
            self.cizim_alani.image = resimtk

    def resmi_boyutlandir(self, resim, max_boyut=500):
        if len(resim.shape) == 3:
            yukseklik, genislik, _ = resim.shape
        else:
            yukseklik, genislik = resim.shape
        olcek_faktoru = max_boyut / max(yukseklik, genislik)
        return cv2.resize(resim, None, fx=olcek_faktoru, fy=olcek_faktoru, interpolation=cv2.INTER_LINEAR)

if __name__ == "__main__":
    window = Tk()
    uygulama = Uygulama(window, "CNN ile Rakam Tahmin Etme")
