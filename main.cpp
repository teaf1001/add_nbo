#include <stdint.h> // for uint8_t
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

uint32_t my_ntohl(uint32_t a) {
    uint32_t a1 = (a & 0xFF000000) >> 3 * 8;
    uint32_t a2 = (a & 0x00FF0000) >> 8;
    uint32_t a3 = (a & 0x0000FF00) << 8;
    uint32_t a4 = (a & 0x000000FF) << 3 * 8;
    return a1 | a2 | a3 | a4;
}

int main(int argc, char* argv[])
{
    //FILE *Pfh = fopen("./five-hundred.bin", "rb");//500
    //FILE *Pth = fopen("./thousand.bin", "rb"); //1000
    FILE *Pfh = fopen(argv[1], "rb");//500
    FILE *Pth = fopen(argv[2], "rb"); //1000

    uint8_t fh[4] = {0};//500 array
    uint8_t th[4] = {0};//1000 array

    fread(fh, sizeof(uint8_t), 4, Pfh);
    fread(th, sizeof(uint8_t), 4, Pth);

    uint32_t* p = reinterpret_cast<uint32_t*>(fh);
    uint32_t n = *p;
    uint32_t* q = reinterpret_cast<uint32_t*>(th);
    uint32_t m = *q;

   //convert network byte order to host byte order
    uint32_t fivehundred = ntohl(n);
    uint32_t thousand = ntohl(m);

    //0x1f4 + 0x3e8 = 0x5dc
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x) ", thousand, thousand, fivehundred, fivehundred, fivehundred+thousand, fivehundred+thousand);

}
