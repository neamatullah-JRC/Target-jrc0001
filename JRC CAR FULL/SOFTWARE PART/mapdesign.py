import pygame

# Initialize Pygame
pygame.init()

# Set the window size
window_size = (600, 400)

# Create the window
screen = pygame.display.set_mode(window_size)

# Set the title of the window
pygame.display.set_caption("Custom Road Map")

# Set the background color
bg_color = (255, 255, 255)

# Initialize a list to store the road segments
road_segments = []

# Set the width of the road segments
road_width = 50

# Set the color of the road segments
road_color = (0, 0, 0)

# Run the game loop
running = True
while running:
    # Check for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Get the mouse position
            mouse_x, mouse_y = pygame.mouse.get_pos()
            # Add a new road segment to the list
            road_segments.append((mouse_x, mouse_y, road_width, road_color))
    # Clear the screen
    screen.fill(bg_color)
    # Draw all of the road segments
    for road_segment in road_segments:
        pygame.draw.rect(screen, road_segment[3], (road_segment[0] - road_segment[2] // 2, road_segment[1] - road_segment[2] // 2, road_segment[2], road_segment[2]))
    # Update the display
    pygame.display.flip()

# Quit Pygame
pygame.quit()
