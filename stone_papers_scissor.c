#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getcmp()
{
    int x=rand()%3+1;
    return x;
}
void show(int p, int cmp, int *c1, int *c2)
{
    printf("You Chose: %s\tComputer Chose: %s\n",p==1?"Stone":p==2?"Paper":"Scissor",cmp==1?"Stone":cmp==2?"Paper":"Scissor");
    if(p==cmp)
    {
        printf("It's a draw :(\n");
    }
    else if( p==2 && cmp==1 || p==1 && cmp==3 || p==3 && cmp ==2)
    {
        printf("You win this round!\n");
        (*c1)++;
    }
    else
    {
        printf("Computer wins this round\n");
        (*c2)++;
    }
    printf("Your Score: %d\tComputer: %d\n\n", *c1, *c2);
}
int main(){
    int p,c1=0,c2=0;
    srand(time(0));
    printf("\nWelcome to the game!\n");
    do{
        printf("1)Stone\n2)Paper\n3)Scissor\n0)Exit\nEnter your choice: ");
        scanf("%d", &p);
        if(p==0){
        break;
        }
        else if(p>=1 && p<=3){
        show(p, getcmp(),&c1,&c2);
        }
        else{
        printf("\nInvalid Choice\n");
        }
    }
    while(p!=0);
    printf("\nThanks for playing :)");
    return 0;
}