import os
import gmplot
import pandas as pd

df = pd.read_csv('map.csv')

latitude = (df.iloc[:, 0]).tolist()
longitude = (df.iloc[:, 1]).tolist()

map_plot = gmplot.GoogleMapPlotter(latitude[0], longitude[0], 20, apikey="AIzaSyBRlMSnitU6Y1ymBsE48tNMXzH8kc_Ml1A")

# scatter points on the Google map

map_plot.scatter(latitude, longitude, size=15, color ="blue")

# Plot method Draw a line in between given coordinates
map_plot.plot(latitude, longitude, 'black', edge_width=2.2)

map_plot.draw("mappath.html")
os.system("mappath.html")