import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt 
import plotly.plotly as py

pd.set_option('display.max_colwidth', -1)

# Create new dataframe
def create_dataframe(filename):
	df = pd.read_csv(filename)
	df = df.rename(columns = lambda x: x.strip())
	return df

#check if both datasets match
def check_lgas(df1, df2):
	l1 = list(df1['lga_code'])
	l2 = list(df2['lga_code'])

	if len(l1) != len(l2):
		return False

	if len(list(set(l2) - set(l1))) != 0 or len(list(set(l1) - set(l2))) != 0:
		return False

	return True

# bar char of homeless population in each LGA
def bar_chart_homeless_pop(df):
	data = dict(zip(df['lga_code'], df['homeless_ppl_est_per_1000_pop']))
	plt.bar(range(len(data)), data.values(), width=1/1.5)
	plt.xticks(range(len(data)), data.keys(), rotation=90)
	plt.title('LGA Homeless Population per 1000 Residents')
	plt.xlabel('LGA Codes')
	plt.ylabel('Homeless Population per 1000')
	plt.show()
	return

# bar chart of populations in each lga at a given year
def population_chart(df, year):
	data = dict(zip(df['lga_code'], df['tpop_' + str(year)]))
	plt.bar(range(len(data)), data.values(), width=1/1.5)
	plt.xticks(range(len(data)), data.keys(), rotation=90)
	plt.title("LGA Population per LGA in " + str(year))
	plt.xlabel('LGA Codes')
	plt.ylabel('Population')
	plt.show()
	return

# properly created dataframes
df1 = create_dataframe('homelessLGA2015.csv')

df2 = create_dataframe('populationLGA.csv')
new_order_col = ['lga_name', 'lga_code', 'tpop_2011', 'tpop_2012',
                 'tpop_2013', 'tpop_2014', 'tpop_2015', 'tpop_2016']

# new order of columns, for consistency
df2 = df2[new_order_col]

# finding the relationship between both datasets
new_data = {'lga_code': df1['lga_code'], 'lga_name': df1['lga_name']}
new_df = pd.DataFrame(data=new_data)

years = ['2011', '2012', '2013', '2014', '2015', '2016']
for year in years:
	new_df[year] = df1['homeless_ppl_est_per_1000_pop'] * (df2['tpop_' + year]/1000)

pd.set_option('display.max_rows', len(new_df))

new_df.to_csv('data.csv', index=False)

#print(df1.nlargest(5, 'social_housing_as_a_perc_of_total_dwellings'))

def create_scatter(col1, col2):
	x = [x for x in df1[col1]]
	y = [y for y in df1[col2]]

	plt.scatter(x, y)

	plt.title('Correlation between Homeless population and Social Housing')
	plt.xlabel('Homeless Population per 1000 people 2011')
	plt.ylabel('Percentage of Social Housing')

	plt.show()

	return

def calculate_pearsons_corr(col1, col2):
	return df1[col1].corr(df1[col2])

create_scatter('homeless_ppl_est_per_1000_pop', 'social_housing_as_a_perc_of_total_dwellings')

print(calculate_pearsons_corr('homeless_ppl_est_per_1000_pop', 'social_housing_as_a_perc_of_total_dwellings'))


