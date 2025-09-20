import socket
import struct
import time

# Define the same structure format as in C++
# int16_t seq, int8_t row, char text[16]
# => 'h' (short), 'i' (byte), '16s' (16-byte string)
STRUCT_FORMAT = '<hb16s'

esp_ip = "192.168.1.62"
esp_port = 10000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((esp_ip, esp_port))
print("Connected to ESP32")

# have to give time for esp32 to be ready to recive
time.sleep(2)

seq = 0
row = 0
text = b"Hello from PC :3"

packed_data = struct.pack(
    STRUCT_FORMAT,
    seq,
    row,
    text.ljust(16, b'\x00')
)
print("Packed length:", len(packed_data))

sock.sendall(packed_data)
print(f"Sent: seq={seq}, row={row}, text={text}")