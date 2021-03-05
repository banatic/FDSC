#include <stdio.h>
#include <string.h>

#define MAX_STRLEN 255

int failure[MAX_STRLEN] = {0, };

/*
failure example

 a b c a b c a c a b
-1-1-1 0 1 2 3-1 0 1 
*/

void printFailure(char* pat){
  int pat_len = strlen(pat);
  for(int temp=0; temp<pat_len; temp++){
    printf(" %c", pat[temp]);
  }
  printf("\n");
  for(int temp=0; temp<pat_len; temp++){
    printf("%2d", failure[temp]);
  }
}

void fail_init(char* pat){
  int p_len = strlen(pat);
  
  failure[0] = -1;
  for(int p_pos = 1; p_pos < p_len; p_pos++){
    int max_fail = failure[p_pos - 1];
    while((pat[p_pos]!=pat[max_fail+1]) && max_fail != -1)
      max_fail = failure[max_fail];
    if(pat[p_pos]==pat[max_fail+1])
      failure[p_pos] = max_fail+1;
    else
      failure[p_pos] = -1;
  }
}

int KMP(char* string, char* pat){
  int s_pos = 0, p_pos = 0;
  int s_len = strlen(string), p_len = strlen(pat);

  while(s_pos < s_len && p_pos < p_len){
    if(string[s_pos] == pat[p_pos]){
      s_pos++; p_pos++;
    }else if(p_pos == 0){
      s_pos++;
    }else{
      p_pos = failure[p_pos - 1] + 1;
    }
  }
  return ((p_pos == p_len) ? (s_pos - p_len) : -1);
}


int main(){
  char pat[] = "abcabcacab";
  
  fail_init(pat);
  printFailure(pat);

}
