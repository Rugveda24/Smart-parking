import serial
import requests

serial_port = 'COM3' 
baud_rate = 9600

thingspeak_channel_id = '2470765' 
thingspeak_api_key = 'XZF5QA1IQ7XU9NJD' 
thingspeak_api_url = f'https://api.thingspeak.com/update?api_key={thingspeak_api_key}'

ser = serial.Serial(serial_port, baud_rate)
while True: 
    data = ser.readline().decode('utf-8').strip() 
    print("Received data:", data)
    
    # Check if the line contains expected substrings
    if 'Slot Available' in data:
        try:
            # Extract numeric values from the received data
            slot_str = data.split('Slot Available = ')[1].split('%')[0]
            print(slot_str)
            slot = int(slot_str)

            # Send data to ThingSpeak
            params = {'field1': slot}
            response = requests.post(thingspeak_api_url, params=params)

            print("ThingSpeak Response:", response.text)
        except (ValueError, IndexError) as e:
            print(f"Error processing data: {e}. Skipping.")
    else:
        print("Invalid data format. Skipping.")
