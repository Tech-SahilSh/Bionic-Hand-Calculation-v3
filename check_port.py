import serial
arduino = serial.Serial('COM6', 9600)
arduino.close()
print("Port is free!")
