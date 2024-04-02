#include <stdio.h>
#include <iostream>
using namespace std;

// Create a matrix with 512 * 512
int m = 3, A[512][512];

/*

generate function parameters:

    n: The size of the sub-board currently being processed.
    x and y: coordinates of the upper left corner of the subboard.
    hx and hy: coordinates of the specified missing cell.

*/
void generate(int n, int x, int y, int hx, int hy)
{
    /*
    Recursive baseline case:
        When n is 2, the board is already 2 × 2 in size, 
        and each cell is filled directly. 
        Skip missing cells during filling.
    */
    if(n == 2)
    {
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                if(x+i != hx || y+j != hy)
                    A[x+i][y+j] = m++/3;
        return;
    }
    /*
    Recursive steps:

    For each 2 × 2 subboard, 
    first check whether it is within the specified region of the missing cell. 
    If so, call the generate function recursively to process this sub-board; 
    otherwise, fill the position of the missing cell with a middle triangle 
    (because this position is not within the current sub-board).
    When the generate function is called recursively, 
    the current sub-board is divided into four equal sub-boards and processed in sequence.
    
    Filling rules:
    Each time it is filled, the variable m is used to control the number of filling.
    Every time a cell is filled, the m value is increased by one, 
    and m/3 is used to get the number on each cell. 
    This ensures that grids of the same shape are filled with the same number. 
    */
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            if(x + i*n/2 > hx || hx >= x + i*n/2+n/2 || y + j*n/2 > hy || hy >= y + j*n/2+n/2)
                // Middle triangle
                A[x+n/2-1+i][y+n/2-1+j] = m++/3; 
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            if(x + i*n/2 <= hx && hx < x + i*n/2+n/2 && y + j*n/2 <= hy && hy < y + j*n/2+n/2)
                // Contains the hole
                generate(n/2, x + i*n/2, y + j*n/2, hx, hy); 
            else 
                // Not contain the hole
                generate(n/2, x + i*n/2, y + j*n/2, x + n/2 - 1 + i, y + n/2 - 1 + j);
}

// Print the result
int main()
{
    int n, px, py;
    scanf("%d %d %d", &n, &px, &py);
    int s = [] (int n) { int i = 1; while(n--) i*=2; return i; }(n);
    generate(s, 0, 0, px-1, py-1);
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < s; j++)
            printf("%d ", A[i][j]);
            
        printf("\n");    
    }
}