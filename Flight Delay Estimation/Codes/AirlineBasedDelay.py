import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# CSV dosyasını oku
df = pd.read_csv("flights2015.csv")

# Havayolu isimlerini gruplayarak ortalama gecikmeyi hesapla
average_delay_by_airline = df.groupby('AIRLINE')['DEPARTURE_DELAY'].mean().reset_index()

# Görselleştirme
plt.figure(figsize=(12, 6))
sns.barplot(x='AIRLINE', y='DEPARTURE_DELAY', data=average_delay_by_airline, palette='viridis')
plt.xticks(rotation=45, ha='right')
plt.title('Havayolu Bazında Ortalama Gecikme Süreleri')
plt.xlabel('Havayolu')
plt.ylabel('Ortalama Gecikme Süresi')
plt.show()