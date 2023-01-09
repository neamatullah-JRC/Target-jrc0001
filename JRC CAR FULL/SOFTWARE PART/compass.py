import pygame
import serial

pygame.init()

# Set the window size
WIDTH, HEIGHT = 700, 700

# Create the window
screen = pygame.display.set_mode((WIDTH, HEIGHT))

# Set the window title
pygame.display.set_caption("Compass")

# Load the compass rose and needle images
rose_image = pygame.image.load("./image/icon.png")
needle_image = pygame.image.load("./image/icon.png")

# Get the center coordinates of the images
rose_rect = rose_image.get_rect(center=(WIDTH // 2, HEIGHT // 2))
needle_rect = needle_image.get_rect(center=(WIDTH // 2, HEIGHT // 2))
font = pygame.font.Font(None, 36)
# Open the serial port
ser = serial.Serial('/dev/ttyACM0', 115200)

# Main game loop
running = True
while running:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            
    # Read the angle from the serial port
   # angle = int(ser.readline())
    buffer = ser.readline()
    print (buffer)
    x = buffer.split()
    angle = int(x[3])
    fd = int(x[0])
    ld = int(x[1])
    rd = int(x[2])
    # Rotate the needle image
    rotated_needle = pygame.transform.rotate(needle_image, angle)
    # Get the new rect of the rotated image
    needle_rect = rotated_needle.get_rect(center=needle_rect.center)
    
    fd = font.render(f"fornt: {fd}", True, (0, 0, 0))
    fd_rect = fd.get_rect()
    fd_rect.center = (100, 50)
     


    
    ld = font.render(f"left: {ld}", True, (0, 0, 0))
    ld_rect = ld.get_rect()
    ld_rect.center = (250, 50)




    rd = font.render(f"right: {rd}", True, (0, 0, 0))
    rd_rect = rd.get_rect()
    rd_rect.center = (400, 50)

    screen.fill((255, 255, 255))
    
    # Draw the compass rose and needle images on the screen
    #screen.blit(rose_image, rose_rect)
    screen.blit(rotated_needle, needle_rect)
    screen.blit(fd, fd_rect)  
    screen.blit(ld, ld_rect)
    screen.blit(rd, rd_rect)  
  

    # Update the display
    pygame.display.flip()

# Close the serial port
ser.close()

# Quit Pygame
pygame.quit()