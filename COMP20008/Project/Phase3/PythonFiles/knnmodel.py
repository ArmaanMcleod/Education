# KNN means

# import prepintegration.py
import prepintegration

#import necessary libraries for this module
from sklearn import neighbors
from sklearn.cross_validation import train_test_split
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
from sklearn.tree import DecisionTreeClassifier

# libraries from prepintegration.py
import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt 
import plotly.plotly as py


df1 = prepintegration.df1

#features list
feature_columns = ['social_housing_count', 'drug_offences', 'rental_housing',
                    'born_overseas', 'unemployment_rate', 'year_12_Education', 'support', 'Population_2015']
# grab features
feature_data = df1[feature_columns]

#class label for testing
class_label = df1['homeless_count']

def create_boxplot(dataframe, column):
    """
    Outputs boxplot of homelessness
    
    Args:
        dataframe: dataframe which we are interested in
        column: which column to create plot for
    Returns:
        None
    """
    data = {'Homelessness per LGA': dataframe[column]}
    
    df = pd.DataFrame(data=data)
    
    df.boxplot(column = 'Homelessness per LGA')
    
    plt.show()
    
    return

# boxplot of homeless distribution
plt.title('Homelessness distribution')
plt.ylabel('Homelessness counts per 1000 population')    
create_boxplot(df1, 'homeless_count')

# information concerning boxplot, such as median and mean
print(class_label.describe())

# Chose these threshholds
threshold1 = 2.1
threshold2 = 3.5

def create_label_map(class_label, threshold1, threshold2):
    """
    Maps values of homeless count to a class label
    
    Args:
        class_label: A pandas series
    Returns:
        mapped label data
    """
    labels = [i for i in class_label]
    for i, e in enumerate(class_label):
        if e <= threshold1:
            labels[i] = 1
        if threshold1 < e <= threshold2:
            labels[i] = 2
        if e > threshold2:
            labels[i] = 3
    return labels

# CODE FROM HERE:
# Taken from workshop 8, and slightly modified to suit my task

# Create new class_label
class_label = pd.Series(create_label_map(class_label, threshold1, threshold2))

# select 66% of instances to be training data, and the rest 33% will be testing data
X_train, X_test, y_train, y_test = train_test_split(feature_data, class_label, train_size=0.66, random_state=42)

# normalise the data to have 0 mean and unit variance using the library functions.  This will help for later
# computation of distances between instances
scaler = preprocessing.StandardScaler().fit(X_train)
X_train=scaler.transform(X_train)
X_test=scaler.transform(X_test)

# looking at knn with k = 7
knn = neighbors.KNeighborsClassifier(n_neighbors=7)
knn.fit(X_train, y_train)

# predictions for each instance,using the class label. Comparison between prediction and actual class label
y_pred=knn.predict(X_test)

# overall accuracy
print(accuracy_score(y_test, y_pred))

# possible ranges of k
ks = range(1, len(feature_columns)+1)

# plotting optimal k values
def optimal_k(ks, X_train, y_train, X_test, y_test):
    """
    Finds optimal k values.
    Code taken from Workshop 8 solutions
    
    Args:
        ks: possible k values
        X_train: x training data
        y_train: y training data
        X_test: x testing data
        y_test: y testing data
    Returns:
        list of accuracies
    """
    accuracies = []
    for k in ks:
        knn = neighbors.KNeighborsClassifier(n_neighbors=k)
        knn.fit(X_train, y_train) 
        y_pred = knn.predict(X_test)
        accuracies.append(accuracy_score(y_test, y_pred))
    return accuracies

accuracies = optimal_k(ks, X_train, y_train, X_test, y_test)

# k versus prediction accuracy
plt.scatter(ks, accuracies)
plt.title('k versus Prediction accuracy')
plt.xlabel('k')
plt.ylabel('Predition Accuracy')
plt.show()

# decision tree
dt = DecisionTreeClassifier(criterion="entropy",random_state=1, max_depth=3)
dt.fit(X_train, y_train)

# Another prediction, for each of the test instances, a prediction for a class label is made.Compare this between the real
# class label.
y_pred=dt.predict(X_test)

# overall accuracy
print(accuracy_score(y_test, y_pred))

# decision tree classification accuracy as the size of training set, which is varied between 10% and 90%
# demonstrates which training size is most accurate
splits = range(10,95,5)

def optimal_training_size(feature_data, class_label):
    """
    returns list of training sizes against prediction accuracies
    Code taken from Workshop 8 solutions
    
    Args:
        feature_data: the relevent features to be compared with
        class_label: the label of the data
    Returns 
        list of training sizes
    """
    accuracies=[]
    for split in splits:
        X_train, X_test, y_train, y_test = train_test_split(feature_data, class_label, train_size=split/100, random_state=42)
        scaler = preprocessing.StandardScaler().fit(X_train)
        X_train=scaler.transform(X_train)
        X_test=scaler.transform(X_test)
        dt.fit(X_train, y_train)
        y_pred=dt.predict(X_test)
        accuracies.append(accuracy_score(y_test, y_pred))
    return accuracies
    
# scatter plot of training sizes
accuracies = optimal_training_size(feature_data, class_label)
plt.scatter(splits, accuracies)
plt.title('Training size versus prediction accuracy')
plt.xlabel('Training size')
plt.ylabel('Prediction Accuracy')
plt.show()