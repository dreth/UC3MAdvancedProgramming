# importing the data
data = pd.read_pickle("wind_pickle.pickle")

# dropping cols
data.drop(['steps', 'month', 'day', 'hour'], axis=1, inplace=True)

# introducing missing values
my_NIA = 34291182
np.random.seed(my_NIA)

# selecting 10% of cols except year and energy
cols = list(set(data.columns) - {'year', 'energy'})
cols_selected = [np.random.choice(cols) for x in range(int(len(cols)*0.1))]

# adding 5% missing values at random places
for col in cols_selected:
    selected_indexes = [np.random.choice(
        data.index) for x in range(int(len(data)*0.05))]
    data[col] = data[col]
