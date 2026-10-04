#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Structure for storing a Collatz sequence */
typedef struct
{
    unsigned long long *data;
    size_t size;
    size_t capacity;
} Sequence;


/* Initialize the dynamic sequence */
void initSequence(Sequence *seq)
{
    seq->capacity = 16;
    seq->size = 0;

    seq->data = malloc(seq->capacity *
                       sizeof(unsigned long long));

    if (seq->data == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}


/* Add a value to the sequence */
void addValue(Sequence *seq,
              unsigned long long value)
{
    if (seq->size == seq->capacity)
    {
        seq->capacity *= 2;

        unsigned long long *temp =
            realloc(seq->data,
                    seq->capacity *
                    sizeof(unsigned long long));

        if (temp == NULL)
        {
            printf("Memory reallocation failed.\n");
            free(seq->data);
            exit(EXIT_FAILURE);
        }

        seq->data = temp;
    }

    seq->data[seq->size] = value;
    seq->size++;
}


/* Free dynamically allocated memory */
void freeSequence(Sequence *seq)
{
    free(seq->data);
    seq->data = NULL;
    seq->size = 0;
    seq->capacity = 0;
}


/*
   Generate the Collatz sequence.

   Returns:
   1  -> sequence reached 1
   0  -> overflow detected
*/
int generateCollatz(unsigned long long start,
                    Sequence *seq)
{
    unsigned long long n = start;

    addValue(seq, n);

    while (n != 1)
    {
        if (n % 2 == 0)
        {
            /*
               Even case:
               n = n / 2
            */
            n = n / 2;
        }
        else
        {
            /*
               Odd case:
               n = 3*n + 1

               Check for overflow before
               performing the multiplication.
            */

            if (n > (ULLONG_MAX - 1) / 3)
            {
                return 0;
            }

            n = 3 * n + 1;
        }

        addValue(seq, n);
    }

    return 1;
}


/* Print a sequence */
void printSequence(const Sequence *seq)
{
    for (size_t i = 0; i < seq->size; i++)
    {
        printf("%llu", seq->data[i]);

        if (i + 1 < seq->size)
        {
            printf(" -> ");
        }
    }

    printf("\n");
}


/* Process one starting number */
void processNumber(unsigned long long start)
{
    Sequence seq;

    initSequence(&seq);

    printf("\nStarting number: %llu\n", start);

    int success = generateCollatz(start, &seq);

    printSequence(&seq);

    if (success)
    {
        printf("Steps to reach 1: %zu\n",
               seq.size - 1);
    }
    else
    {
        printf("Overflow detected before the sequence "
               "could be continued safely.\n");
    }

    freeSequence(&seq);
}


/* Main function */
int main()
{
    unsigned long long start, end;

    printf("Enter start of interval: ");
    scanf("%llu", &start);

    printf("Enter end of interval: ");
    scanf("%llu", &end);

    if (start == 0 || end == 0 || start > end)
    {
        printf("Invalid interval.\n");
        return 1;
    }

    for (unsigned long long n = start;
         n <= end;
         n++)
    {
        processNumber(n);

        /*
           Prevent unsigned integer wraparound
           when n == ULLONG_MAX.
        */
        if (n == ULLONG_MAX)
        {
            break;
        }
    }

    return 0;
}