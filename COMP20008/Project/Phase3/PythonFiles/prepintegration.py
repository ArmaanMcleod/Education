import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt 
import plotly.plotly as py

# Create new dataframe
def create_dataframe(filename):
    """
    Creates a dataframe from filename specified.
    Also strips any whitespace for columns headers.
    
    Args:
        filename: a string specifying dataset in csv format
    Returns:
        a pandas dataframe corresponding to the dataset provided
    """

    df = pd.read_csv(filename)
    
    # strips whitespace
    df = df.rename(columns = lambda x: x.strip())
    return df

def check_lgas(df1, df2):
    """
    Some preprocessing checking in order to check if both dataframes
    contain same amount of LGAs. 
    
    Args:
        df1: first dataframe corresponding to dataset 1
        df2: second dataframe corresponding to dataset 2
    Returns:
        true if both dataframes match, false if not
    """
    
    # convert lga codes into lists
    l1 = list(df1['lga_code'])
    l2 = list(df2['lga_code'])

    if len(l1) != len(l2):
	    return False

    # check if any values are not common in both dataframes
    if len(list(set(l2) - set(l1))) != 0 or len(list(set(l1) - set(l2))) != 0:
	    return False

    return True

def bar_chart_homeless_pop(df):
    """
    A function used in phase 2 to show bar charts of the homeless populations
    
    Args:
        df: the dataframe to be plotted
    Returns:
        bar chart of homeless
    """
    data = dict(zip(df['lga_code'], df['homeless_ppl_est_per_1000_pop']))
    plt.bar(range(len(data)), data.values(), width=1/1.5)
    plt.xticks(range(len(data)), data.keys(), rotation=90)
    plt.title('LGA Homeless Population per 1000 Residents')
    plt.xlabel('LGA Codes')
    plt.ylabel('Homeless Population per 1000')
    plt.show()
    return

# scatter plot between two columns
def create_scatter(col1, col2):
    """
    Creates scatter plot of two variables, col1 and col2.
    Args:
        col1: first variable
        col2: second variable
    Returns:
        scatter plot of both variables
    """
    
    # put the columns into lists, easier to work with
    x = [x for x in df1[col1]]
    y = [y for y in df1[col2]]

    plt.scatter(x, y)

    plt.show()

    return


def calculate_pearsons_corr(col1, col2):
    """
    Calculates pearsons correlation of two variables.
    Args:
        col1: first variable
        col2: second variable
    Returns:
        returns correlation coefficient
    """
    return df1[col1].corr(df1[col2])

# creating dataframes for datasets
df1 = create_dataframe('dataset1.csv')
df2 = create_dataframe('dataset2.csv')

#reordering columns
new_order_col = ['lga_name', 'lga_code', 'homeless_ppl_est_per_1000_pop', 'social_housing_dwellings', 
                 'drug_usage_and_possession_offences_per_1000_pop', 'rental_housing_that_is_affordable_perc', 
                 'ppl_born_overseas_perc', 'unemployment_rate_perc','ppl_who_did_not_complete_yr_12_perc', 
                 'ppl_who_are_def_able_to_get_help_from_nbrs_perc']

df1 = df1[new_order_col]

#Adding population to first dataframe
df1['Population_2015'] = df2['tpop_2015']

# new column names, since the above are too long and hard to index
new_cols = ['lga_name', 'lga_code', 'homeless_count', 'social_housing_count', 'drug_offences', 'rental_housing',
              'born_overseas', 'unemployment_rate', 'year_12_Education', 'support', 'Population_2015']

# renaming columns. 
df1.columns = new_cols

def scatterplots_to_screen(col1, col2):
    """
    Outputs scatter plot of two varaibles, along with correlations
    
    Args:
        col1: the first variable
        col2: the second variable
    Returns:
        None
    """
    create_scatter(col1, col2)
    print("Correlation: " + str(calculate_pearsons_corr(col1, col2)))
    return

# All the scatter plots of each feature
# Since different titles and labels are used, this proccess is very repetitive.
plt.title('Homelessness vs Social Housing per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('Social housing dwellings per LGA')
scatterplots_to_screen('homeless_count', 'social_housing_count')

plt.title('Homelessness vs Drug Usage per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('Drug Usage per LGA')
scatterplots_to_screen('homeless_count', 'drug_offences')

plt.title('Homelessness vs Rental Housing Affordability per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('Rental Housing percentages')
scatterplots_to_screen('homeless_count', 'rental_housing')

plt.title('Homelessness vs People born overseas per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('People born overseas percentage')
scatterplots_to_screen('homeless_count', 'born_overseas')

plt.title('Homelessness vs Unemployment rate percentage per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('Unemployment rate percentage')
scatterplots_to_screen('homeless_count', 'unemployment_rate')

plt.title('Homelessness vs People without Year 12 percentage per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('People who did not finish Year 12 percentage')
scatterplots_to_screen('homeless_count', 'year_12_Education')

plt.title('Homelessness vs People able to get social support per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('People able to get help from social support percentage')
scatterplots_to_screen('homeless_count', 'support')

plt.title('Homelessness vs Population per LGA')
plt.xlabel('Homeless people per 1000 population')
plt.ylabel('LGA Population 2015')
scatterplots_to_screen('homeless_count', 'Population_2015')

# correlation data used for matrix
correlation_data = {'homeless_count':df1['homeless_count'], 'social_housing_count':df1['social_housing_count'], 
                    'drug_offences': df1['drug_offences'], 'rental_housing': df1['rental_housing'],
                    'born_overseas': df1['born_overseas'], 'unemployment_rate': df1['unemployment_rate'], 
                    'year_12_Education': df1['year_12_Education'], 'support': df1['support'], 
                    'Population_2015': df1['Population_2015']}

# converting correlation data to dataframe
correlation_df = pd.DataFrame(data = correlation_data)


def create_correlation_matrix(df, columns):
    """
    Outputs correlation matrix of dataframe.
    Code taken from http://machinelearningmastery.com/visualize-machine-learning-data-python-pandas/
    
    Args:
        df: the dataframe to calculate correlation
        columns: column headers to include in correlation
    Returns:
        None
    """
    correlations = df.corr()
    fig = plt.figure()
    ax = fig.add_subplot(111)
    cax = ax.matshow(correlations, vmin=-1, vmax=1)
    fig.colorbar(cax)
    ticks = np.arange(0,9,1)
    ax.set_xticks(ticks)
    ax.set_yticks(ticks)
    ax.set_xticklabels(columns, rotation = 90)
    ax.set_yticklabels(columns)
    plt.show()
    return

# creates correlation matrix
create_correlation_matrix(correlation_df, new_cols[2:])