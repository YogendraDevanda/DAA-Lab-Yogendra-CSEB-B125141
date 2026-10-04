#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

/* Check whether 3*n + 1 will overflow */
int safe_odd_step(ull n, ull *result)
{
    if (n > (ULLONG_MAX - 1) / 3)
        return 0;

    *result = 3 * n + 1;
    return 1;
}

/* Perform one Collatz step */
int collatz_step(ull n, ull *next)
{
    if (n == 0)
        return 0;

    if (n % 2 == 0)
    {
        *next = n / 2;
        return 1;
    }
    else
    {
        return safe_odd_step(n, next);
    }
}

/* Generate and print the trajectory */
int analyze_trajectory(ull start)
{
    ull n = start;
    ull next;
    ull steps = 0;
    ull capacity = 16;
    ull *path;

    path = (ull *)malloc(capacity * sizeof(ull));

    if (path == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("\nTrajectory for %llu:\n", start);

    while (1)
    {
        if (steps >= capacity)
        {
            capacity *= 2;

            ull *temp = (ull *)realloc(path,
                                       capacity * sizeof(ull));

            if (temp == NULL)
            {
                printf("\nMemory reallocation failed.\n");
                free(path);
                return 0;
            }

            path = temp;
        }

        path[steps] = n;

        if (n == 1)
            break;

        if (!collatz_step(n, &next))
        {
            printf("\nInteger overflow detected at %llu.\n", n);
            free(path);
            return 0;
        }

        n = next;
        steps++;
    }

    for (ull i = 0; i <= steps; i++)
    {
        printf("%llu", path[i]);

        if (i < steps)
            printf(" -> ");
    }

    printf("\nNumber of steps = %llu\n", steps);

    free(path);

    return 1;
}

/* Calculate number of steps without storing trajectory */
int collatz_steps(ull start, ull *steps)
{
    ull n = start;
    *steps = 0;

    while (n != 1)
    {
        ull next;

        if (!collatz_step(n, &next))
            return 0;

        n = next;
        (*steps)++;
    }

    return 1;
}

/* Analyze all starting values in [a,b] */
void analyze_interval(ull a, ull b)
{
    ull totalSteps = 0;
    ull maximumSteps = 0;
    ull maxStart = a;

    printf("\nInterval Analysis [%llu, %llu]\n", a, b);

    for (ull i = a; i <= b; i++)
    {
        ull steps;

        if (!collatz_steps(i, &steps))
        {
            printf("Overflow detected for starting value %llu\n", i);
            continue;
        }

        printf("%llu -> %llu steps\n", i, steps);

        totalSteps += steps;

        if (steps > maximumSteps)
        {
            maximumSteps = steps;
            maxStart = i;
        }

        if (i == ULLONG_MAX)
            break;
    }

    printf("\nMaximum steps = %llu\n", maximumSteps);
    printf("Starting value producing maximum steps = %llu\n",
           maxStart);

    printf("Total steps = %llu\n", totalSteps);
}

/* Main function */
int main()
{
    int choice;
    ull n, a, b;

    printf("===== COLLatz CONJECTURE ANALYZER =====\n");

    printf("\n1. Analyze one starting value");
    printf("\n2. Analyze an interval");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter starting value n (>1): ");
        scanf("%llu", &n);

        if (n <= 1)
        {
            printf("Starting value must be greater than 1.\n");
            return 0;
        }

        analyze_trajectory(n);
    }
    else if (choice == 2)
    {
        printf("Enter interval [a,b]: ");
        scanf("%llu %llu", &a, &b);

        if (a < 1 || a > b)
        {
            printf("Invalid interval.\n");
            return 0;
        }

        analyze_interval(a, b);
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}