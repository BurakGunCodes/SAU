import pandas as pd
from joblib import load

# Eğitilmiş modelin yüklenmesi
loaded_model = load("egitilmis_model_rf.joblib")

# Kullanıcı Girişi
user_input = {
    'SCHEDULED_DEPARTURE': [450],
    'DISTANCE': [1000],
    'MONTH': [1],
    'DAY': [10],
    'DAY_OF_WEEK': [4],
}

# Girdiyi DataFrame'e dönüştürün
input_df = pd.DataFrame(user_input)

# Modeli kullanarak kalkış gecikmesini tahmin edin
predicted_departure_delay = loaded_model.predict(input_df)
print(f"Tahmini Kalkış Gecikmesi: {predicted_departure_delay[0]:.2f} dakika")
