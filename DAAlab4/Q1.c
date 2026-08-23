#include<stdio.h>
#include<string.h>
typedef struct item{
    int number;
    char color[10];

} item;
 int main(){  
    int n;
    printf("enter value of n : ");
    scanf("%d ",&n);
    item arr[n];
    item result[n];

    printf("enter number and clour : ");
    for(int i=0;i<n;i++){
        scanf("%d %s ",&arr[i].number,arr[i].color);
        printf("\n");
    }
    int k=0;
 //red colur copy
    for(int i=0;i<n;i++){
       if(strcmp(arr[i].color,"red")==0){
          result[k++]= arr[i];
        }
    }
 //blue colur copy
    for(int i=0;i<n;i++){
       if(strcmp(arr[i].color,"blue")==0){
          result[k++]= arr[i];
        }
    }
 //tellow colur copy
    for(int i=0;i<n;i++){
       if(strcmp(arr[i].color,"yellow")==0){
          result[k++]= arr[i];
        }
    }
    printf("  sorted array ");
    for(int i=0;i<n;i++){
        printf("%d %s ",result[i].number,result[i].color);
        printf("\n");
    }

    return 0;
 }