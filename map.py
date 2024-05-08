import folium
import pandas as pd

# Define your coordinates
file = pd.read_csv("output.csv")

route_coordinates = list(zip(file["latitude"], file["longitude"]))
middle = (int)(len(route_coordinates)/2)
# Create a base map
m = folium.Map(location=route_coordinates[middle], zoom_start=17)

folium.Marker(location=route_coordinates[0], popup="Start point").add_to(m)
folium.Marker(location=route_coordinates[-1], popup="End point").add_to(m)

# Add markers for each location
folium.PolyLine(
    locations=route_coordinates,
    color='blue',
    weight=15,
    opacity=0.8
).add_to(m)

# Save the map as HTML
m.save("route.html")

print("Map created as map.html. Open it in a web browser to view.")