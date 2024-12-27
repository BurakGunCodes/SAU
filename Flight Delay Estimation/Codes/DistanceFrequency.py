import matplotlib.pyplot as plt
import pandas as pd

# CSV dosyasını oku
df = pd.read_csv("flights2015.csv")

# Korelasyonu hesapla
correlation = df['DISTANCE'].corr(df['DEPARTURE_DELAY'])

# Sonucu yazdır
print("Korelasyon Katsayısı:", correlation)

# Histogram oluştur
plt.hist(df['DISTANCE'], bins=20, color='blue', edgecolor='black')

# Grafik başlığı ve etiketleri ekle
plt.title('Mesafe Dağılımı')
plt.xlabel('Mesafe (km)')
plt.ylabel('Sıklık')

# Histogramı göster
plt.show()