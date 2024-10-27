#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int num, guess, nguess = 0;
    srand(time(0));
    num = rand() % 100 + 1;
    // printf("The number is %d \n", num);
    do
    {
        printf("\nGuess the number between 0 and 100: ");
        scanf("%d", &guess);
        if (guess > num)
            printf("Lower number please!\n");
        else if (guess < num)
        {
            printf("Higher number please!\n");
        }
        else
            printf("\nCongratulations, you guessed the number in %d attemps \n", nguess);
        nguess++;
    } while (guess != num);
    return 0;
}