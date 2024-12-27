import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error
from joblib import dump
from math import sqrt  # RMSE için


# Veri setini yükleyin 
chunk_size = 10000
data_chunks = pd.read_csv("flights2015.csv", usecols=['DEPARTURE_DELAY', 'SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK'], chunksize=chunk_size)

# Modeli tanımlayın
model = RandomForestRegressor(n_estimators=10, random_state=42)

for i, data_chunk in enumerate(data_chunks):
    print(f"Eğitim seti parça {i + 1}")
    
    # İlgili sütunları seçin
    selected_columns = ['DEPARTURE_DELAY', 'SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']
    data_chunk = data_chunk[selected_columns]

    # Eksik değerleri içeren satırları düşürün
    data_chunk = data_chunk.dropna()

    # Modeli eğitmek için özellikler ve hedef değişkeni seçin
    features = data_chunk[['SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']]
    target = data_chunk['DEPARTURE_DELAY']

    # Eğitim setini oluşturun
    X_train, _, y_train, _ = train_test_split(features, target, test_size=0.2, random_state=42)

    # Modeli eğitin
    model.fit(X_train, y_train)

# Model performansını değerlendirin
# Bu kısmı ihtiyaca göre dışarıda bir değerlendirme seti ile değiştirebilirsiniz
predictions = model.predict(X_train)
mse = mean_squared_error(y_train, predictions)
rmse = sqrt(mse)  # RMSE hesaplanıyor
print(f"Mean Squared Error: {mse}")
print(f"Root Mean Squared Error: {rmse}")


# Eğitilmiş modeli diske kaydedin
dump(model, "egitilmis_model_rf.joblib")

# Örnek bir girişi kullanarak modeli test edin
user_input = {
    'SCHEDULED_DEPARTURE': [1500],
    'DISTANCE': [3000],
    'MONTH': [10],
    'DAY': [1],
    'DAY_OF_WEEK': [4],
}

# Girdiyi DataFrame'e dönüştürün
input_df = pd.DataFrame(user_input)

# Modeli kullanarak kalkış gecikmesini tahmin edin
predicted_departure_delay = model.predict(input_df)
print(f"Tahmini Kalkış Gecikmesi: {predicted_departure_delay[0]:.2f} dakika")

