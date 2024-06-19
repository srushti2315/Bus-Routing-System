import json
import time
import requests

def geocode_place(place_name, max_retries=3, retry_delay=1):
    base_url = "https://nominatim.openstreetmap.org/search"
    params = {
        "q": place_name,
        "format": "json",
        "limit": 1
    }

    retries = 0
    while retries < max_retries:
        try:
            response = requests.get(base_url, params=params)
            response.raise_for_status()  # Raise an exception for 4xx or 5xx status codes
            data = response.json()
            if data:
                location = data[0]
                return location["lat"], location["lon"]
            else:
                return None, None
        except requests.exceptions.RequestException as e:
            print(f"Error while geocoding place '{place_name}': {e}")
            retries += 1
            if retries < max_retries:
                print(f"Retrying in {retry_delay} seconds...")
                time.sleep(retry_delay)
            else:
                print("Max retries exceeded.")
                return None, None

def add_coordinates_to_json(input_file, output_file):
    with open(input_file, 'r') as f:
        data = json.load(f)

    for place in data["places"]:
        latitude, longitude = geocode_place(place["place_name"])
        place["latitude"] = latitude
        place["longitude"] = longitude

    with open(output_file, 'w') as f:
        json.dump(data, f, indent=4)

# Example usage
add_coordinates_to_json('assets/routes.json', 'assets/routes2.json')
