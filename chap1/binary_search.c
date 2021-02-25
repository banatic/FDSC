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

int binary_search(int find_v){
    int left, middle, right;
    left = 0; right = LIST_SIZE-1; middle = (left + right) / 2;
    while(left <= right){
        if(find_v < list[middle]){
            right = middle - 1;
        }else if(find_v == list[middle]){
            return middle;
        }else if(find_v > list[middle]){
            left = middle + 1;
        }
        middle = (left + right) / 2;
    }
    return -1;
}

int main(){
    printf("List init (sorted) : "); list_init(); selection_sort(); list_print();
    printf("find value : ");
    
    int find_v;
    scanf("%d", &find_v);
    find_v = binary_search(find_v);
    if(find_v==-1) printf("None\n");
    else printf("pos : %d\n", find_v + 1);

    return 0;
}
