#include <stdio.h>
#include <string.h>

void f(int x, int * y);

int main(void){

    char s1[] = "zoey";
    char s2[] = "zoey";
    char * s3 = s1;
    char * s4 = s2;
    printf("1. sizeof(s1) = %lu\n", sizeof(s1));
    if(s1 == s2) printf("2. s1 == s2 is true\n");
    else printf("2. s1 == s2 is false\n");
    if(strcmp(s3, s4) == 0) printf("3. (strcmp(s3, s4) == 0) is true\n");
    else printf("3. (strcmp(s3, s4) == 0) is false\n");
    double d[5] = {7.5, 2.8, 9.5, 88.7, 1.7};
    int v[4];
    for(size_t i = 0; i < 4; i++){
        *(v + i) = (int) ((unsigned long) &d[i+1] - (unsigned long) &d[i]);
    }

    printf("4. The values stored in v are ");
    for(int i = 0; i < 4; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
    char * p1 = &s4[0];
    *p1 = 'j';
    *(&s4[3]) = 's';
    char * s5 = "zoey\0 is awesome";
    printf("5. s4 = %s, s5 = %s\n", s4, s5);
    int q[5];
    int * p2 = q;
    for(int i = 1; i < 6; i++) *(p2 + i - 1) = i * 5;
    f(*(q + 1), (q + 2));
    printf("6. What is the value of (q[1] + q[2])?\n");
    printf("%d\n", q[1] +q[2]);
    printf("7. p2 = %ld, q = %ld\n", (unsigned long) p2, (unsigned long) q);
    printf("8. p2 = %p, q = %p\n", (void *) p2, (void *) q);
    return 0;
}

void f(int x, int * y){
    x = -2;
    *y = -3;
}
