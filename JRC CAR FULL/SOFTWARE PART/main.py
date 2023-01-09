import pygame
import serial

pygame.init()

WIDTH, HEIGHT = 700, 700


logo = logo = pygame.image.load("./image/logo.jpeg")


# Draw a red circle

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_icon(logo)
pygame.display.set_caption("JRC CAR")

needle_image = pygame.image.load("./image/icon.png")

needle_rect = needle_image.get_rect(center=(WIDTH // 2, HEIGHT // 2))
font = pygame.font.Font(None, 36)
ser = serial.Serial('/dev/rfcomm0', 9600)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            
    buffer = ser.readline()
    print (buffer)
    x = buffer.split()
    angle = int(x[3])
    fd = int(x[0])
    ld = int(x[1])
    rd = int(x[2])
    rotated_needle = pygame.transform.rotate(needle_image, angle)
    needle_rect = rotated_needle.get_rect(center=needle_rect.center)
    
    fdvalue = font.render(f"fornt: {fd}", True, (0, 0, 0))
    fdvalue_rect = fdvalue.get_rect()
    fdvalue_rect.center = (100, 50)
     
    
    ldvalue = font.render(f"left: {ld}", True, (0, 0, 0))
    ldvalue_rect = ldvalue.get_rect()
    ldvalue_rect.center = (250, 50)

    rdvalue = font.render(f"right: {rd}", True, (0, 0, 0))
    rdvalue_rect = rdvalue.get_rect()
    rdvalue_rect.center = (400, 50)

    screen.fill((255, 255, 255))
    
    screen.blit(rotated_needle, needle_rect)
    screen.blit(fdvalue, fdvalue_rect)  
    screen.blit(ldvalue, ldvalue_rect)
    screen.blit(rdvalue, rdvalue_rect)  
    if 0 < fd < 10:
        fdcolor = pygame.Color(255, 0, 0)
    else:
        fdcolor = pygame.Color(0, 255, 0)
    if 0 < ld < 10:
        ldcolor = pygame.Color(255, 0, 0)
    else:
        ldcolor = pygame.Color(0, 255, 0)
    if 0 < rd < 10:
        rdcolor = pygame.Color(255, 0, 0)
    else:
        rdcolor = pygame.Color(0, 255, 0)
# Draw a circle with the chosen fdcolor
    pygame.draw.circle(screen, fdcolor, (100, 100), 10)  # center at 
    pygame.draw.circle(screen, ldcolor, (250, 100), 10)  # center at 
    pygame.draw.circle(screen, rdcolor, (400, 100), 10)  # center at 

    pygame.display.flip()

ser.close()

pygame.quit()