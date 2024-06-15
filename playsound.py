import serial
import time
import pygame
import tkinter as tk

# Initialize Pygame mixer
pygame.mixer.init()



# Load the sound files
sound_file_1 = "Bark.mp3"  # Replace with your first file path
sound_file_2 = "whining.mp3"  # Replace with your second file path

# Set up the serial port
ser = serial.Serial('/dev/cu.usbmodem11401', 9600)  # Replace 'COM3' with your Arduino's serial port
time.sleep(2)  # Wait for the serial connection to initialize

def send_command(command):
    ser.write(command.encode())

'''
# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((300, 200))
pygame.display.set_caption("Arduino Control")

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_s:
                print("Key 's' pressed - Sending command to Arduino")
                send_command('s')
                pygame.mixer.music.load(sound_file_1)
                pygame.mixer.music.play()
            elif event.key == pygame.K_q: 
                running = False

    screen.fill((255, 255, 255))  # Fill the screen with white
    pygame.display.flip()

pygame.quit()


'''
while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print(line)
        if line == "Second tap detected - Starting motor":
            pygame.mixer.music.load(sound_file_1)
            pygame.mixer.music.play()
        
