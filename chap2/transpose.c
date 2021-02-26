#include <stdio.h>
#include <time.h>

#define MAX_TERMS   101     /* 희소 행렬에서의 최대 항의 개수 + 1 */
#define MAX_COL     30      /* Fast transpose용                   */
typedef struct sparse_maxtrix{
    int col;
    int row;
    int value;
    }s_matrix;

s_matrix a[MAX_TERMS];
s_matrix b[MAX_TERMS]; /* 전치용 빈 Matrix */


void init_matrix(){
   a[0].row = 6; a[0].col = 6; a[0].value = 8; //행의 수, 열의 수, 항의 총 수
   a[1].row = 0; a[1].col = 0; a[1].value = 2;
   a[2].row = 0; a[2].col = 3; a[2].value = 3;
   a[3].row = 0; a[3].col = 5; a[3].value = 4;
   a[4].row = 1; a[4].col = 1; a[4].value = 5;
   a[5].row = 1; a[5].col = 2; a[5].value = 6;
   a[6].row = 2; a[6].col = 3; a[6].value = 7;
   a[7].row = 4; a[7].col = 0; a[7].value = 8;
   a[8].row = 5; a[8].col = 2; a[8].value = 9;
}

void print_matrix(s_matrix matrix[]){
    printf("        row   col   val\n");
    for(int temp=0; matrix[temp].value; temp++){
        printf("M[%d] %5d %5d %5d\n", temp, matrix[temp].row, matrix[temp].col, matrix[temp].value);
    }
}

void transpose(){
    /* O(n^2) */
    b[0].row = a[0].col; b[0].col = a[0].row; b[0].value = a[0].value; /* header copy */
    int _count = 1;
    for(int _col=0; _col<a[0].col; _col++){
        for(int _temp=1; _temp<=a[0].value; _temp++){
            if(a[_temp].col == _col){
                b[_count].row = a[_temp].col;
                b[_count].col = a[_temp].row;
                b[_count].value = a[_temp].value;
                _count++;
            }
        }
    }
}

void fast_transpose(){
    /* O(n) */
    int row_terms[MAX_COL] = {0, }, starting_pos[MAX_COL] = {1, 0, };
    b[0].row = a[0].col; b[0].col = a[0].row; b[0].value = a[0].value; /* header copy */
    for(int i = 1; i<=a[0].value; i++){
        row_terms[a[i].col]++;
    }
    for(int i = 1; i<a[0].col; i++){
    starting_pos[i] = starting_pos[i - 1] + row_terms[i-1];
    }
    for(int i =1; i<= a[0].value; i++){
        int j = starting_pos[a[i].col]++;
        b[j].row = a[i].col; b[j].col = a[i].row; b[j].value = a[i].value;
    }
}


double tick(void (*fp)()){
    clock_t start = clock(), diff;
    fp();
    diff = clock() - start;
    double msec = diff * 1000.0f / CLOCKS_PER_SEC;
    return msec;
}

int main(){
    init_matrix();
    print_matrix(a);
    
    double _tick = tick(*transpose);
    /*
    print_matrix(b);
    printf("Regular transpose : %f ms\n", _tick);
    
    _tick = tick(*fast_transpose);
    print_matrix(b);
    printf("fast transpose : %f ms\n", _tick);
    */
    
    const int iteration = 1000;

    _tick = 0;
    for(int i=0; i<iteration; i++){
        _tick += tick(*transpose);
    }
    printf("Avg of regular transpose : %f us\n", _tick * 1000 / iteration);

    _tick = 0;
    for(int i=0; i<iteration; i++){
        _tick += tick(*fast_transpose);
    }

    printf("Avg of fast transpose : %f us\n", _tick * 1000 / iteration);
    
    return 0;
}
