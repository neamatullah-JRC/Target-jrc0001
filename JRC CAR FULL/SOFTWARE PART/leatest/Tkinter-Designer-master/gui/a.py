import tkinter as tk

colors = ["red", "orange", "yellow", "green", "blue", "purple"]

# Create the main window
window = tk.Tk()
window.title("New Year Wish")

# Create a label with the message
message = tk.Label(text="Happy New Year!", font=("Helvetica", 32))
message.pack()

# Create a button that closes the window when clicked
def close_window():
    window.destroy()

button = tk.Button(text="Close", command=close_window)
button.pack()

# Pulse the label by changing its color
def pulse():
    color = colors[0]
    colors.append(colors.pop(0))
    message.configure(fg=color)
    window.after(500, pulse)

# Start the pulse animation
window.after(500, pulse)

# Start the GUI event loop
window.mainloop()
