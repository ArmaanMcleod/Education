import pandas as pd 

pd.set_option('display.max_colwidth', -1)

non_homeless_permitted = ['Open to everyone',
						  'General community, people on low incomes, people with disabilities and/or poor mental health',
						  'Open to everyone, not just students. '
						  'You don’t have to be a member or a volunteer to eat at the Melbourne University Food Co-op, '
						  'however membership entitles you to 10% on everything. On top of that, '
						  'volunteering 2 hours per week gets you a free meal and 20% off everything.',
						  'People living in the City of Melbourne who are homeless or sleeping rough and who have trouble '
						  'cooking for themselves or buying healthy meals. Program membership is required.',
						  'People experiencing disadvantage in the City of Melbourne',
						  'Open to all adults aged over 18 years']

not_needed_columns = ['Social Media', 'Contact Person', 'Website', 'Phone 2', 'Alternate Website', 
                      'Email', 'Freecall', 'Enter Via', 'What', 'Who', 'Access', 'Tram routes', 
                      'Public Holidays', 'Nearest train station', 'Bus routes', 'Car parking', 
                      'Bicycle parking', 'Walking', 'Geocoded Location', 'Category Number', 'Sub Category', 
                      'Special Dietary Requirements 1', 'Special Dietary Requirements 2', 'Special Dietary Requirements 3']

data = pd.read_csv("Community_Food_Map.csv")

data = data[data['Who'].isin(non_homeless_permitted)]

for col in not_needed_columns:
	del data[col]

data = data[~data['Name'].isin(['Café Meals - Homeless'])]
data = data[~data['Category'].isin(['Food Delivery and Shopping Support Services', 'Food Growing Education'])]




