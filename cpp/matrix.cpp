#include<iostream>
#include<string>
#include<wiringPi.h>
#include<time.h>
#include "matrix.h"

using namespace std;

#define LINES 16
#define HIGH 1
#define LOW 0

// 1 - OFF, 0 - ON
int matrix[LINES][LINES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0}
};

Matrix::Matrix(int D, int C, int B, int A, int G, int DI, int CLK, int LAT)
{
    this->D = D;
    this->C = C;
    this->B = B;
    this->A = A;
    this->G = G;
    this->DI = DI;
    this->CLK = CLK;
    this->LAT = LAT;

    wiringPiSetupPhys();

    pinMode(D, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(A, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(DI, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(LAT, OUTPUT);
}

void Matrix::Delay(long int nanoseconds)
{
    delayMicroseconds(nanoseconds / 100); // ~ 10 ns
}

void Matrix::LineSelect(int line)
{
    if(line > LINES)
        return;
    
    int b[4];
    
    for (int i = 0; i < 4; i++)
    {
        b[i] = param >> i;
        b[i] = b[i] & 0x1;
    }

    digitalWrite(D, b[3]);
    digitalWrite(C, b[2]);
    digitalWrite(B, b[1]);
    digitalWrite(A, b[0]);
}

void Matrix::Draw(int draw[16][16])
{
    for (int line = 0; line < LINES; line++)
    {
        digitalWrite(G, LOW);
        digitalWrite(LAT, LOW);
        digitalWrite(CLK, LOW);

        for (int column = 0; column < LINES; column++)
        {
            //Delay(1);

            digitalWrite(DI, draw[line][column]);

            //Delay(1);
            digitalWrite(CLK, 1);

            //Delay(1);
            digitalWrite(CLK, 0);
        }

        digitalWrite(LAT, 1);
        //Delay(1);
    }
}

int i(char * param)
{
    return strtol(param, nullptr, 10);
}

int main(int argc, char** argv)
{
if (argc != 9)
    {
        cout << "Faulty pin parameters - D C B A G DI CLK LAT";
        return 1;
    }

    Matrix led = Matrix(
        i(argv[1]),
        i(argv[2]),
        i(argv[3]),
        i(argv[4]),
        i(argv[5]),
        i(argv[6]),
        i(argv[7]),
        i(argv[8])
    );

    while (true)
    {
        led.Draw(matrix);
        led.Delay(1);
    }
}