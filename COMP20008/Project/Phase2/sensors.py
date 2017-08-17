import pandas as pd 

pd.set_option('display.max_colwidth', -1)

csv_data = pd.read_csv('Pedestrian_sensor_locations.csv')

not_needed_cols = ['Upload Date', 'Year Installed', 'Status', 'Location Type', "Geometry"]

for col in not_needed_cols:
	del csv_data[col]
