from flask import Flask, render_template, request, jsonify
import serial
import time

app = Flask(__name__)

arduino = serial.Serial(port='COM6', baudrate=9600, timeout=1)
time.sleep(2)  # Wait for Arduino reset

def number_to_finger_byte(num):
    states = 0b00000
    if num >= 1: states |= (1 << 1)
    if num >= 2: states |= (1 << 2)
    if num >= 3: states |= (1 << 3)
    if num >= 4: states |= (1 << 4)
    if num >= 5: states |= (1 << 0)
    return states

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/send', methods=['POST'])
def send_number():
    data = request.json
    result = data['result']

    if result < 0: result = 0
    if result > 5: result = 5

    byte_value = number_to_finger_byte(result)
    arduino.write(bytes([byte_value]))
    return jsonify({'status': 'ok', 'sent': bin(byte_value)})

@app.route('/reset', methods=['POST'])
def reset_fingers():
    arduino.write(bytes([0b00000]))
    return jsonify({'status': 'reset'})

if __name__ == '__main__':
    app.run(debug=True)
