txt = "welcome to the jungle"

x = txt.split()
y=0
print(x)
for y in range (len(x)):
	print(x[y])
	y+=1



text = font.render(f"fornt: {fd}", True, (0, 0, 0))
text_rect = text.get_rect()
text_rect.center = (100, 50)






screen.blit(text, text_rect)  
