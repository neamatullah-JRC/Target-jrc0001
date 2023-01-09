import pygame, sys
import serial


ser = serial.Serial('/dev/ttyACM0',9600)

buffer = ""
 
mainClock = pygame.time.Clock()
from pygame.locals import *
pygame.init()
pygame.display.set_caption('game base')
screen = pygame.display.set_mode((700, 700),0,32)
img = pygame.image.load('./image/icon.png').convert()
img.set_colorkey((0,0,0))
 
angle = 0
while True:
    buffer = ser.readline()
    print (buffer)
    x = buffer.split()
    print(x[3])
    screen.fill((0,50,0))
    img = pygame.transform.rotate(img, x[3])
    screen.blit(img, (100,100))
    pygame.display.update()
