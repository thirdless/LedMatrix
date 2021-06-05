import sys
import os
from time import sleep
import RPi.GPIO as GPIO

LINES = 16

# 1 - OFF, 0 - ON
matrix = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0]
]

class Matrix:

    def Delay(self, timp):
        sleep(timp / 100000000.0) # ~ 10 ns

    def __LineSelect(self, line):
        if line >= LINES:
            return

        b = [0] * 4

        for i in range(0, 4):
            b[i] = line >> i
            b[i] = b[i] & 0x1

        GPIO.output(self.__D, b[3])
        GPIO.output(self.__C, b[2])
        GPIO.output(self.__B, b[1])
        GPIO.output(self.__A, b[0])


    def Draw(self, array):

        for line in range(0, LINES):
            GPIO.output(self.__G, 0)
            GPIO.output(self.__LAT, 0)
            GPIO.output(self.__CLK, 0)
            
            self.__LineSelect(line)

            for column in range(0, LINES):
                #self.Delay(1)

                GPIO.output(self.__DI, array[line][column])

                #self.Delay(1)
                GPIO.output(self.__CLK, 1)

                #self.Delay(1)
                GPIO.output(self.__CLK, 0)

            GPIO.output(self.__LAT, 1)
            #self.Delay(1)


    def __init__(self, D, C, B, A, G, DI, CLK, LAT):
        self.__D = D
        self.__C = C
        self.__B = B
        self.__A = A
        self.__G = G
        self.__DI = DI
        self.__CLK = CLK
        self.__LAT = LAT

        GPIO.setmode(GPIO.BOARD)

        GPIO.setup(D, GPIO.OUT)
        GPIO.setup(C, GPIO.OUT)
        GPIO.setup(B, GPIO.OUT)
        GPIO.setup(A, GPIO.OUT)
        GPIO.setup(G, GPIO.OUT)
        GPIO.setup(DI, GPIO.OUT)
        GPIO.setup(CLK, GPIO.OUT)
        GPIO.setup(LAT, GPIO.OUT)

def main():
    if len(sys.argv) is not 9:
        print("Faulty pin parameters - D C B A G DI CLK LAT")
        exit(1)

    led = Matrix(
        int(sys.argv[1]),
        int(sys.argv[2]),
        int(sys.argv[3]),
        int(sys.argv[4]),
        int(sys.argv[5]),
        int(sys.argv[6]),
        int(sys.argv[7]),
        int(sys.argv[8])
    )

    while True:
        led.Draw(matrix)
        led.Delay(1)

main()