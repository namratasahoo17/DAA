#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long bubbleEarlyExit(int a[], int n)
{
    long comparisons = 0;

    for(int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for(int j = 0; j < n - 1 - i; j++)
        {
            comparisons++;

            if(a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }

        if(!swapped)
            break;
    }

    return comparisons;
}

long bubbleFullPass(int a[], int n)
{
    long comparisons = 0;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1 - i; j++)
        {
            comparisons++;

            if(a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main()
{
    srand(time(NULL));

    FILE *fp = fopen("bubble_data.csv", "w");

    if(fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }

    fprintf(fp, "ArraySize,EarlyExit,FullPass\n");

    printf("\nBubble Sort Comparison Analysis\n\n");
    printf("%-10s %-15s %-15s\n",
           "Size",
           "Early Exit",
           "Full Pass");

    for(int n = 100; n <= 2000; n += 100)
    {
        int *a1 = (int *)malloc(n * sizeof(int));
        int *a2 = (int *)malloc(n * sizeof(int));

        if(a1 == NULL || a2 == NULL)
        {
            printf("Memory Allocation Failed!\n");
            return 1;
        }

        for(int i = 0; i < n; i++)
        {
            int value = rand() % 10000;
            a1[i] = value;
            a2[i] = value;
        }

        long early = bubbleEarlyExit(a1, n);
        long full = bubbleFullPass(a2, n);

        printf("%-10d %-15ld %-15ld\n",
               n,
               early,
               full);

        fprintf(fp,
                "%d,%ld,%ld\n",
                n,
                early,
                full);

        free(a1);
        free(a2);
    }

    fclose(fp);

    printf("\nCSV file generated successfully.\n");

    FILE *py = fopen("plot_q3.py", "w");

    if(py == NULL)
    {
        printf("Error creating Python script.\n");
        return 1;
    }

    fprintf(py,"import pandas as pd\n");
    fprintf(py,"import matplotlib.pyplot as plt\n\n");

    fprintf(py,"df = pd.read_csv('bubble_data.csv')\n\n");

    fprintf(py,"plt.figure(figsize=(10,6))\n");
    fprintf(py,"plt.plot(df['ArraySize'], df['EarlyExit'], marker='o', linewidth=2, label='Early Exit Bubble Sort')\n");
    fprintf(py,"plt.plot(df['ArraySize'], df['FullPass'], marker='s', linewidth=2, label='Full Pass Bubble Sort')\n");
    fprintf(py,"plt.xlabel('Array Size (n)')\n");
    fprintf(py,"plt.ylabel('Number of Comparisons')\n");
    fprintf(py,"plt.title('Bubble Sort Performance Analysis')\n");
    fprintf(py,"plt.grid(True)\n");
    fprintf(py,"plt.legend()\n");
    fprintf(py,"plt.tight_layout()\n");
    fprintf(py,"plt.savefig('Q3_BubbleSort.png', dpi=300)\n");
    fprintf(py,"plt.show()\n");

    fclose(py);

    printf("Generating graph...\n");

    system("python plot_q3.py");

    printf("Graph saved as Q3_BubbleSort.png\n");

    return 0;
}