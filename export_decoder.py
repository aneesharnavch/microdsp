import base64
import json
import csv

# Decode the MicroDSP base64-exported string into a dictionary
def decode_microdsp_string(encoded_str):
    try:
        decoded_bytes = base64.b64decode(encoded_str.encode("utf-8"))
        decoded_str = decoded_bytes.decode("utf-8")
        data = json.loads(decoded_str)
        return data
    except Exception as e:
        print("[Decoder Error]:", e)
        return None

# Save data list to CSV
def save_to_csv(data_dict, path):
    try:
        with open(path, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Type", data_dict.get("type", "unknown")])
            writer.writerow(["Index", "Value"])
            for i, val in enumerate(data_dict.get("data", [])):
                writer.writerow([i, val])
        print("Saved to:", path)
    except Exception as e:
        print("[CSV Save Error]:", e)

# === Example Usage ===
if __name__ == "__main__":
    x = input("Paste exported MicroDSP string: ")
    output_path = input("Enter path to save CSV (e.g. output.csv): ")

    decoded = decode_microdsp_string(x)
    if decoded:
        save_to_csv(decoded, output_path)
    else:
        print("Could not decode the input string.")
