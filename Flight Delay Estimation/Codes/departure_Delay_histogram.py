import pandas as pd
import matplotlib.pyplot as plt

# Veri setini yükleyin
data = pd.read_csv("flights2015.csv")


plt.hist(data['DEPARTURE_DELAY'], bins=50, range=(-100, 100), edgecolor='black')
plt.xlabel('Rötar Süresi')
plt.ylabel('Sıklık')
plt.title('-100 dk ile +100 dk arası Rötar Süre Sıklığı')
plt.show()
