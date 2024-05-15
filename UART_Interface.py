import serial.tools.list_ports
import csv
import os

# Get a list of all COM ports
com_ports = serial.tools.list_ports.comports()

# Initialize the selected port
selected_port = serial.Serial(baudrate=9600, timeout=1)

# Select the desired Port from the port list
for port in com_ports:
    port_name = port.device     # get the port name
    print("Found: " + port_name)
    ipt = input("Is this is the desired port? [Y,N]")
    if ipt.upper() == 'Y':      # If this is the desired port
        selected_port.port = port_name  # Set the name of the selected port
        try:
            selected_port.open()    # Open the port
        except serial.SerialException:
            print("Failed to open the port")
            exit(1)
        break   # Exit the loop
# selected_port.read() # Read the port
# selected_port.write('S')
# data = selected_port.read(34)
# print(f"Encoded data = {data}")
# decoded = data.decode()
# print(f"Decoded data = {decoded}")
# If no port is selected exit the program
if not selected_port.port:
    print("No more COM ports found")
    exit(1)

# ## The Implemented PC-Tiva Interface goes like follows:
# # 1 - The tiva loads the EEPROM data into the memory
# # 2 - Tiva waits until the PC sends a specific bit specifying that PC is ready to recieve
# # 3 - Tiva sends first the size of the data in bytes to PC
# # 4 - PC seynds another character to recieve the actual data
# # 5 - Tiva sends the actual coordinate data & PC fetches and organises data

## The following code is made for the following string configuration:
#  long1,lat1|long2,lat2|long3,lat3|....|long(n),lat(n)

selected_port.write(b'S') # Request size of data
size_bytes = selected_port.read(1) # Reads size in bytes

try: # Convert the data to an integer
    size = int.from_bytes(size_bytes, 'little') # Configuring the decode for little endian
    print(f"Size of the data is {size} Bytes")  
except UnicodeDecodeError:
    print("Invalid data received")
    exit(1)

selected_port.write(b'D') # Request data
data_bytes = selected_port.readall() # Reads data

try: # Put data in a string
    data_string = data_bytes.decode('ascii').strip()
except UnicodeDecodeError:
    print("Invalid data received")
    exit(1)

try:
    selected_port.close() # close the port after usage
except serial.SerialException:
    print("Failed to close the port")

coordinates = data_string.split('|') # Separating individual coordinates

table = [["Latitude", "Longitude"]] # making a list to hold rows

# insert coordinates into the list
for coordinate_str in coordinates:
    coordinate = coordinate_str.split(',')
    table.append(coordinate)

# Open the csv file for writing
with open('output.csv', 'w', os.O_WRONLY | os.O_CREAT | os.O_TRUNC) as f:
    # Create a writer object for the file
    writer = csv.writer(f)

    # Write each row to the CSV file
    writer.writerows(table)

print("Succesfully fetched and put the coordinate data in output.csv file")