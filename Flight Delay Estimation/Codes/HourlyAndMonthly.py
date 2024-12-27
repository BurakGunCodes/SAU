"""

YEAR,
MONTH,
DAY,
DAY_OF_WEEK,
AIRLINE,
FLIGHT_NUMBER,
TAIL_NUMBER,
ORIGIN_AIRPORT,
DESTINATION_AIRPORT,
SCHEDULED_DEPARTURE,
DEPARTURE_TIME,
DEPARTURE_DELAY,
TAXI_OUT,
WHEELS_OFF,
SCHEDULED_TIME,
ELAPSED_TIME,
AIR_TIME,
DISTANCE,
WHEELS_ON,
TAXI_IN,
SCHEDULED_ARRIVAL,
ARRIVAL_TIME,
ARRIVAL_DELAY,
DIVERTED,
CANCELLED,
CANCELLATION_REASON,
AIR_SYSTEM_DELAY,
SECURITY_DELAY,
AIRLINE_DELAY,
LATE_AIRCRAFT_DELAY,
WEATHER_DELAY



"""

from collections import Counter
import numpy as np
import pandas as pd
from datetime import datetime


cancelled = 0
counter = Counter()

# 12 AY 
month_counter = [None] * 13
for i in range(13):
    month_counter[i] = Counter()

# 0-23 arası 24 saat
hour_counter = [None] * 24
for i in range(24):
    hour_counter[i] = Counter()

time_classifications= Counter()

chunk_size = 10000  # Örnek olarak 10000 satır parça parça okuma
# "object" şekilde her iki sütun da metin olarak okunur ve sayısal bir işlem yapılmaz.
for chunk in pd.read_csv(
    "flights2015.csv",
    na_values=[" "],
    keep_default_na=False,
    dtype={"SCHEDULED_DEPARTURE": object,"DEPARTURE_TIME": object}, 
    chunksize=chunk_size, 
    #nrows=400000
    ):

    #origin_airport = chunk["ORIGIN_AIRPORT"]



    for index, row in chunk.iterrows():
        
        schedule_time = row["SCHEDULED_DEPARTURE"]
        departure_time = row["DEPARTURE_TIME"]
        month = row["MONTH"]

        #print(f"dep:{departure_time}")
        # verilerin boş gelmediğinden emin oluuyoruz
        if (schedule_time and departure_time and month):
            if schedule_time == 2400:
                schedule_time = 0000
                
            if departure_time == "2400":
                #print(f"dx0:{departure_time}")
                departure_time = "0000"
                #print(f"dx1:{departure_time}")

            #print(f"d0:{departure_time}")
            scheduled_datetime = datetime.strptime(schedule_time, "%H%M").time()
            departured_datetime = datetime.strptime(departure_time, "%H%M").time()
            #print(f"d1:{departure_time}")

            s_hour = scheduled_datetime.hour
            s_min = scheduled_datetime.minute

            d_hour = departured_datetime.hour
            d_min = departured_datetime.minute

            #print(f"s:{s_hour,s_min}, d: {d_hour,d_min}")
            # İki saat arasındaki farkı hesaplayalım
            time_difference = datetime.combine(datetime.min, scheduled_datetime) - datetime.combine(datetime.min, departured_datetime)

            # Farkı yazdıralım
            # Farkın pozitif veya negatif olup olmadığını kontrol edelim
            #print(f"m:{month}")
            if time_difference.total_seconds() > 0:
                
                time_classifications["early"] += 1
                hour_counter[s_hour]["early"] += 1
                month_counter[month]["early"] += 1

            elif time_difference.total_seconds() < 0:
                time_classifications["delayed"] += 1
                hour_counter[s_hour]["delayed"] += 1
                month_counter[month]["delayed"] += 1

            else:
                time_classifications["on_time"] += 1
                hour_counter[s_hour]["on_time"] += 1
                month_counter[month]["on_time"] += 1

        else:
            #hour_counter[s_hour]["cancelled"] += 1
            cancelled += 1
            
#print(hour_counter)
print(month_counter)

# Histogramı oluşturmak için matplotlib kullanabilirsiniz
import matplotlib.pyplot as plt

fig, (hourly, monthly) = plt.subplots(1, 2,sharey=True)

""" 
categories = list(time_classifications.keys())
counts = list(time_classifications.values())

plt.bar(categories, counts)
plt.xlabel("Time Classification")
plt.ylabel("Count")
plt.title("Time Classification Histogram")
plt.show()
 """

hours = np.arange(0,23,1)

"""
categories = list(hour_counter[1].keys())
counts = list(hour_counter[1].values())
print(categories,counts)
"""

# Burada hangi saatte ne kadar gecikme, erken veya tam vaktinde kalkış olduğu çizdirildi
bar_width = 0.3
for i in range(24):

    hourly.bar(i - bar_width, hour_counter[i]["early"], width=bar_width ,color="Blue")
    hourly.bar(i , hour_counter[i]["delayed"], width=bar_width, color="Red")
    hourly.bar(i + bar_width, hour_counter[i]["on_time"], width=bar_width, color="Green")

hourly.set_title("Saatlik")
hourly.legend(["Early", "Delayed", "On Time"],loc="upper left")
hourly.set_xticks([ i for i in range(24)],[f"{i}-{i+1}" for i in range(24)],rotation=75)   
hourly.set_xlabel("Saat Aralığı")
hourly.set_ylabel("Kişi Sayısı")

# burada hangi ayda ne kadar gecikme, erken veya tam vaktinde kalkış olduğu çizdirildi

bar_width = 0.3
for i in range(13):

    monthly.bar(i - bar_width, month_counter[i]["early"], width=bar_width ,color="Blue")
    monthly.bar(i , month_counter[i]["delayed"], width=bar_width, color="Red")
    monthly.bar(i + bar_width, month_counter[i]["on_time"], width=bar_width, color="Green")

monthly.set_title("Aylık")
monthly.legend(["Early", "Delayed", "On Time"],loc="upper right")
# Ayların listesi
aylar = ["Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran", 
         "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"]

monthly.set_xticks([ i+1 for i in range(12)],[f"{aylar[i]}" for i in range(12)],rotation=75)   
monthly.set_xlabel("Aylar")
#monthly.set_ylabel("Kişi Sayısı")


print(f"canceled:{cancelled}")

# Yalnızca bir kez legend ekleyin
#plt.legend(["Early", "Delayed", "On Time"],loc="upper left")
"""
# Diğer grafik ayarlarınızı yapın
plt.xticks([ i for i in range(24)],[f"{i}-{i+1}" for i in range(24)],rotation=75)
plt.xlabel("Saat")
plt.ylabel("Count")
plt.title("Saatlik Uçuş Durumu")
"""
# Grafiği göster
plt.show()


#scheduled time - departured time
# fark +: early 0: on time -: delayed 


