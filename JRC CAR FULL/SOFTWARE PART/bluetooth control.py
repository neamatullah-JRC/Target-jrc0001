import tkinter as tk
import serial

# Define the serial port and baud rate for the Bluetooth connection
PORT = '/dev/ttyBluetooth'
BAUD_RATE = 9600

# Open a serial connection to the Arduino
ser = serial.Serial(PORT, BAUD_RATE)

# Create the main window
window = tk.Tk()
window.title('Bluetooth Car Control')

# Define the forward, backward, left, and right commands
CMD_FORWARD = b'F'
CMD_BACKWARD = b'B'
CMD_LEFT = b'L'
CMD_RIGHT = b'R'

# Define the function that is called when the Forward button is clicked
def move_forward():
    ser.write(CMD_FORWARD)

# Define the function that is called when the Backward button is clicked
def move_backward():
    ser.write(CMD_BACKWARD)

# Define the function that is called when the Left button is clicked
def move_left():
    ser.write(CMD_LEFT)

# Define the function that is called when the Right button is clicked
def move_right():
    ser.write(CMD_RIGHT)

# Create the Forward button and bind it to the move_forward function
btn_forward = tk.Button(window, text='Forward', command=move_forward)
btn_forward.pack()

# Create the Backward button and bind it to the move_backward function
btn_backward = tk.Button(window, text='Backward', command=move_backward)
btn_backward.pack()

# Create the Left button and bind it to the move_left function
btn_left = tk.Button(window, text='Left', command=move_left)
btn_left.pack()

# Create the Right button and bind it to the move_right function
btn_right = tk.Button(window, text='Right', command=move_right)
btn_right.pack()

# Start the GUI loop
window.mainloop()
