import serial

ser = serial.Serial("COM3", 9600, timeout=0)

while True:
    print(ser.readLine())
    time.sleep(1)
        
