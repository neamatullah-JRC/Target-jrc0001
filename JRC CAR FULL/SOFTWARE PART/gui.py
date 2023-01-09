import pygame
import tkinter as tk

# Initialize Pygame
pygame.init()

# Set the window size and title
size = (640, 480)
pygame.display.set_caption("Pygame + Tkinter")

# Create the Pygame window
screen = pygame.display.set_mode(size)

# Create the Tkinter window
tk_window = tk.Tk()

# Create a Tkinter frame to hold the Pygame window
frame = tk.Frame(tk_window)
frame.pack()

# Create a Pygame canvas to display the Pygame window
canvas = pygame.Surface(size)

# Function to update the Pygame window
def update_pygame():
    # Clear the canvas
    canvas.fill((0, 0, 0))
    # Draw something on the canvas
    pygame.draw.circle(canvas, (255, 255, 255), (320, 240), 100)
    # Update the Tkinter label with the canvas image
    image = tk.PhotoImage(data=pygame.image.tostring(canvas, 'RGB'))
    label.config(image=image)
    label.image = image
    # Call this function again after 100 milliseconds
    tk_window.after(100, update_pygame)

# Create a Tkinter label to display the Pygame window
label = tk.Label(frame)
label.pack()

# Start the Pygame loop
update_pygame()

# Run the Tkinter main loop
tk_window.mainloop()

# Quit Pygame
pygame.quit()
