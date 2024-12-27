import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# CSV dosyasını oku
df = pd.read_csv("flights2015.csv")

# NaN değerleri içeren satırları temizle
df = df.dropna(subset=['ORIGIN_AIRPORT'])

# Havaalanı kodlarını stringe dönüştür
df['ORIGIN_AIRPORT'] = df['ORIGIN_AIRPORT'].astype(str)

# ABC gibi harflerden oluşan havaalanları filtrele
filtered_airports = df[df['ORIGIN_AIRPORT'].str.isalpha()]

# Rastgele 30 havaalanı seç
random_airports = np.random.choice(filtered_airports['ORIGIN_AIRPORT'].unique(), size=30, replace=False)

# Seçilen havaalanları içeren DataFrame'i oluştur
selected_airports_df = filtered_airports[filtered_airports['ORIGIN_AIRPORT'].isin(random_airports)]

# Havaalanına göre ortalama, minimum ve maksimum gecikme sürelerini hesapla
delay_stats_by_airport = selected_airports_df.groupby('ORIGIN_AIRPORT')['DEPARTURE_DELAY'].agg(['mean', 'min', 'max']).reset_index()

# Görselleştirmeler
plt.figure(figsize=(16, 8))



# Minimum Gecikme
plt.subplot(3, 1, 1)
sns.barplot(x='ORIGIN_AIRPORT', y='min', data=delay_stats_by_airport, palette='viridis')
plt.title('Havaalanına Göre Minimum Gecikme Süreleri (Rastgele 30 Havaalanı)')
plt.xlabel('Havaalanı')
plt.ylabel('Minimum Gecikme Süresi')

# Maksimum Gecikme
plt.subplot(3, 1, 2)
sns.barplot(x='ORIGIN_AIRPORT', y='max', data=delay_stats_by_airport, palette='viridis')
plt.title('Havaalanına Göre Maksimum Gecikme Süreleri (Rastgele 30 Havaalanı)')
plt.xlabel('Havaalanı')
plt.ylabel('Maksimum Gecikme Süresi')

# Ortalama Gecikme
plt.subplot(3, 1,3)
sns.barplot(x='ORIGIN_AIRPORT', y='mean', data=delay_stats_by_airport, palette='viridis')
plt.title('Havaalanına Göre Ortalama Gecikme Süreleri (Rastgele 30 Havaalanı)')
plt.xlabel('Havaalanı')
plt.ylabel('Ortalama Gecikme Süresi')


plt.tight_layout()  # Grafikler arasındaki boşluğu düzenle
plt.show()