"""
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.metrics import mean_squared_error
from joblib import dump
from math import sqrt  # RMSE için


# Veri setini yükleyin (uygun şekilde ayarladığınızdan emin olun)
data = pd.read_csv("flights2015.csv")

# Sadece DEPARTURE_DELAY sütununu ve ihtiyaç duyduğunuz diğer sütunları seçin
selected_columns = ['DEPARTURE_DELAY', 'SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']
data = data[selected_columns]

# Eksik değerleri içeren satırları düşürün
data = data.dropna()

# Modeli eğitmek için özellikler ve hedef değişkeni seçin
features = data[['SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']]
target = data['DEPARTURE_DELAY']

# Eğitim ve test setlerini oluşturun
X_train, X_test, y_train, y_test = train_test_split(features, target, test_size=0.2, random_state=42)

# Makine öğrenimi boru hattını oluşturun (veri standartlaştırma + regresyon modeli)
model = Pipeline([
    ('scaler', StandardScaler()),
    ('regressor', LinearRegression())
])

# Modeli eğitin
model.fit(X_train, y_train)

# Model performansını değerlendirin
predictions = model.predict(X_test)
mse = mean_squared_error(y_test, predictions)
rmse = sqrt(mse)  # RMSE hesaplanıyor
print(f"Mean Squared Error: {mse}")
print(f"Root Mean Squared Error: {rmse}")

# Eğitilmiş modeli diske kaydedin
dump(model, "egitilmis_model.joblib")

# Örnek bir girişi kullanarak modeli test edin
user_input = {
    'SCHEDULED_DEPARTURE': [15],
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

"""

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.metrics import mean_squared_error
from joblib import dump
from math import sqrt  # RMSE için

# CSV dosyasının yolu ve sütunları belirtilir
file_path = "flights2015.csv"
selected_columns = ['DEPARTURE_DELAY', 'SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']

# Veri setini küçük parçalara bölerek okuma
chunk_size = 10000  # Örneğin, 10,000 satırlık parçalar
data_chunks = pd.read_csv(file_path, usecols=selected_columns, chunksize=chunk_size)

# İlk chunk'ı kullanarak modeli eğitmek için bir Pipeline oluşturun
model = Pipeline([
    ('scaler', StandardScaler()),
    ('regressor', LinearRegression())
])

total_mse = 0.0
total_rmse = 0.0
total_samples = 0

# Her bir chunk ile eğitimi gerçekleştirin
for i, chunk in enumerate(data_chunks):
    print(f"Eğitim seti parça {i + 1}")
    
    # Chunk üzerinde işlemleri gerçekleştirin
    # (Eğitim seti, eksik değerleri düşürme, özellik ve hedef değişkeni seçme, eğitim)
    
    # Eksik değerleri içeren satırları düşürün
    chunk = chunk.dropna()

    # Modeli eğitmek için özellikler ve hedef değişkeni seçin
    features_chunk = chunk[['SCHEDULED_DEPARTURE', 'DISTANCE', 'MONTH', 'DAY', 'DAY_OF_WEEK']]
    target_chunk = chunk['DEPARTURE_DELAY']

    # Eğitim setini oluşturun
    X_train_chunk, _, y_train_chunk, _ = train_test_split(features_chunk, target_chunk, test_size=0.2, random_state=42)

    # Modeli eğitin
    model.fit(X_train_chunk, y_train_chunk)
    
    # Model performansını değerlendirin (her chunk için)
    predictions_chunk = model.predict(X_train_chunk)
    mse_chunk = mean_squared_error(y_train_chunk, predictions_chunk)
    rmse_chunk = sqrt(mse_chunk)
    
    total_samples += len(y_train_chunk)
    total_mse += mse_chunk * len(y_train_chunk)
    total_rmse += rmse_chunk * len(y_train_chunk)

# Toplu olarak MSE ve RMSE değerlerini hesapla
total_mse /= total_samples
total_rmse /= total_samples

print(f"Total Mean Squared Error: {total_mse}")
print(f"Total Root Mean Squared Error: {total_rmse}")

# Eğitilmiş modeli diske kaydedin
dump(model, "egitilmis_model_chunked.joblib")

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
