import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV
df = pd.read_csv('search_time.csv')

# Plot
plt.figure(figsize=(10, 6))
plt.plot(df['Occupancy'], df['Time(sec)'], marker='o', linestyle='-', color='b')
plt.title('Occupancy vs. Average Search Time')
plt.xlabel('Occupancy')
plt.ylabel('Average Search Time (sec)')
plt.grid(True)
plt.show()