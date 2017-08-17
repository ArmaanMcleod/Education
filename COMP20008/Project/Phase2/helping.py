import pandas as pd 

pd.set_option('display.max_colwidth', -1)

data = pd.read_csv('Helping_Out.csv')

new_df = pd.DataFrame(columns = data.columns.values)

valid_rows = [13, 18, 21, 24, 29, 111]

for row in valid_rows:
	new_df.loc[row] = data.ix[row]



