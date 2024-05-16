import joblib
import numpy as np
from time import sleep
import requests

url = "http://172.20.10.6:5001/data"

def test():
    rf_model = joblib.load('random_forest_model.pkl')
    knn_model = joblib.load('knn_model.pkl')

    feature_data = [-99, -31, -22]

    feature_data_array = np.array(feature_data).reshape(1, -1)
    print('feature_data reshaped ', feature_data_array, type(feature_data_array))

    rf_prediction = rf_model.predict(feature_data_array)
    knn_prediction = knn_model.predict(feature_data_array)

    print(rf_prediction)
    print(knn_prediction)
    return


def test_UI():
    data_points = [
        [-77, -75, -75],
        [-80, -77, -70],
        [-78, -75, -72],
        [-70, -68, -74],
        [-83, -71, -69],
        [-79, -78, -73],
        [-76, -70, -66],
        [-74, -75, -70],
        [-81, -68, -70],
        [-68, -64, -72],
        [-73, -80, -66],
        [-69, -75, -81],
        [-73, -72, -75],
        [-62, -74, -71],
        [-56, -79, -77],
        [-72, -83, -85],
        [-79, -76, -75],
        [-82, -80, -65],
        [-83, -80, -81],
        [-67, -79, -74],
        [-64, -72, -62],
        [-87, -84, -69],
        [-84, -87, -73],
        [-85, -82, -72],
        [-85, -78, -75],
        [-89, -91, -73],
        [-88, -81, -74],
        [-80, -79, -79],
        [-84, -85, -80],
        [-85, -81, -83],
        [-83, -82, -80],
        [-79, -84, -78]
    ]
    # Create a list to store the strings
    formatted_data = []

    # Iterate over each row in the data_points list
    for i, row in enumerate(data_points, start=1):
        # Iterate over each value in the row
        for j, value in enumerate(row, start=1):
            # Create the string using the row index (A, B, C) and the value index (1, 2, 3)
            string = f"{chr(64 + j)}={value}={i}"
            # Append the string to the formatted_data list
            formatted_data.append(string)

    for data in formatted_data:
        response = requests.post(url, data=data.encode())
        print(response.status_code)
        sleep(1)

    return

test_UI()




