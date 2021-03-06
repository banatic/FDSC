#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LIST_SIZE 5

int list[LIST_SIZE];

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void list_print(){
    for(int temp=0;temp<LIST_SIZE;temp++){
        printf("%d ", list[temp]);
    }
    printf("\n");
}

void list_init(){
    srand(time(NULL));
    for(int temp=0;temp<LIST_SIZE;temp++){
        list[temp]=rand() % (LIST_SIZE * 2);
    }
}

void selection_sort(){
    int min_pos;

    for(int i=0;i<LIST_SIZE;i++){
        min_pos = i;
        for(int j=i+1;j<LIST_SIZE;j++){
            if(list[j]<list[min_pos]){
                min_pos = j;
            }
        }
        swap(&list[min_pos], &list[i]);
    }
}

int main(){
    list_init();
    printf("List init : "); list_print();
    printf("Selection sort : "); selection_sort(); list_print();
    return 0;
}
