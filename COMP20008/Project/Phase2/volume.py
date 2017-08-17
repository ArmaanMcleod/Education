import matplotlib
import pandas as pd
import numpy as npLawson Wang-Wills
import matplotlib.pyplot as plt

pd.set_option('display.max_colwidth', -1)

csv_data = pd.read_csv('Pedestrian_volume__updated_monthly_.csv')

not_needed_cols = ['ID', 'Date_Time', 'Year', 'Month', 'Mdate', 'Day', 'Time']

for col in not_needed_cols:
	del csv_data[col]

new_data = {'Sensor_ID': csv_data['Sensor_ID'], 'Sensor_Name': csv_data['Sensor_Name'], 'Avg': csv_data['Hourly_Counts']}

new_df = pd.DataFrame(data=new_data)

new_df = new_df.groupby(by = ['Sensor_ID'])['Avg'].mean().to_dict()

plt.bar(range(len(new_df)), new_df.values(), 1/1.5, align = 'center')

plt.xticks(range(len(new_df)), new_df.keys())

plt.show()