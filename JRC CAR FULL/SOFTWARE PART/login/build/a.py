import tkinter as tk

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

# Start the GUI event loop
window.mainloop()
