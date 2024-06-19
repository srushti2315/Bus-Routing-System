import csv
import json

def convert_csv_to_json(input_file, output_file):
    routes = []
    id_count = 1
    
    with open(input_file, 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        
        for row in reader:
            route = {
                "id": str(id_count),
                "Route Description": row["Route Description"],
                "Kilometer": row["Kilometer"]
            }
            routes.append(route)
            id_count += 1
    
    with open(output_file, 'w') as jsonfile:
        json.dump(routes, jsonfile, indent=2)

# Example usage
convert_csv_to_json("assets\bus_routes.csv", "assets\routes.json")
