import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# CSV dosyasını oku
df = pd.read_csv("flights2015.csv")

# NaN değerleri içeren satırları temizle
df = df.dropna(subset=['ORIGIN_AIRPORT'])

# Havaalanı kodlarını stringe dönüştür
df['ORIGIN_AIRPORT'] = df['ORIGIN_AIRPORT'].astype(str)

# ABC gibi harflerden oluşan havaalanları filtrele
filtered_airports = df[df['ORIGIN_AIRPORT'].str.isalpha()]

# Havaalanına göre ortalama gecikme sürelerini hesapla
delay_stats_by_airport = filtered_airports.groupby('ORIGIN_AIRPORT')['DEPARTURE_DELAY'].mean().reset_index()

# 300 havaalanı yerine örneğin en çok gecikme yaşanan ilk 50 havaalanını seç
top_airports = delay_stats_by_airport.sort_values(by='DEPARTURE_DELAY', ascending=False).head(50)

# Görselleştirmeler
plt.figure(figsize=(16, 8))

# Ortalama Gecikme
sns.barplot(x='ORIGIN_AIRPORT', y='DEPARTURE_DELAY', data=top_airports, palette='viridis')
plt.title('Havaalanına Göre Ortalama Gecikme Süreleri (Top 50 Havaalanı)')
plt.xlabel('Havaalanı')
plt.ylabel('Ortalama Gecikme Süresi')

plt.xticks(rotation=45, ha='right')  # Havaalanı isimlerini yatay olarak düzenle
plt.tight_layout()  # Grafikler arasındaki boşluğu düzenle
plt.show()