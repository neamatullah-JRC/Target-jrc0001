import pygame
import gui
# Initialize Pygame
result = gui.update_animation()
pygame.init()

# Set the window size
screen = pygame.display.set_mode((400, 400))

# Create a red color
red = pygame.Color(255, 0, 0)

# Draw a red circle
pygame.draw.circle(screen, red, (100, 100), 10,4)  # center at (100, 100), radius of 10

# Update the display
pygame.display.flip()
gui.update_animation()
# Run the Pygame loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

# Quit Pygame
pygame.quit()
