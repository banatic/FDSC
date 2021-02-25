#include <stdio.h>
#define PERM_SIZE 5

char list[PERM_SIZE];

void swap(char* x, char* y){
    char temp = *x;
    *x = *y;
    *y = temp;
}

void list_init(){
    for(int temp=0; temp<PERM_SIZE; temp++){
        list[temp] = 'a' + temp;
    }
}

void list_print(){
    for(int temp=0; temp<PERM_SIZE; temp++){
        printf("%c ", list[temp]);
    }
    printf("\n");
}

void perm(char* list, int first, int last){
    if(first == last){
        list_print();
    }else{
        for(int temp=first; temp<=last; temp++){
            swap(&list[first], &list[temp]);
            perm(list, first+1, last);
            swap(&list[first], &list[temp]);
        }
    }
}

int main(){
    list_init();
    perm(list, 0, PERM_SIZE-1);

    return 0;
}
