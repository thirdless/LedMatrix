class Matrix{

    int D, C, B, A, G, DI, CLK, LAT;
    void LineSelect(int);
    
public:

    Matrix(int, int, int, int, int, int, int, int);
    void Draw(int[16][16]);
    void Delay(long int);

};