#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int sizes[] = {100, 500, 1000, 2000, 4000};
    int totalSizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("unique_data.csv", "w");

    if(fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }

    fprintf(fp, "ArraySize,Comparisons,Duplicate\n");

    printf("\nElement Uniqueness Analysis\n\n");
    printf("%-12s %-18s %-12s\n",
           "Array Size",
           "Comparisons",
           "Duplicate");

    for(int s = 0; s < totalSizes; s++)
    {
        int n = sizes[s];

        int *a = (int *)malloc(n * sizeof(int));

        if(a == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        for(int i = 0; i < n; i++)
            a[i] = rand();

        long comparisons = 0;
        int duplicate = 0;

        for(int i = 0; i < n && !duplicate; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                comparisons++;

                if(a[i] == a[j])
                {
                    duplicate = 1;
                    break;
                }
            }
        }

        printf("%-12d %-18ld %-12s\n",
               n,
               comparisons,
               duplicate ? "Yes" : "No");

        fprintf(fp,
                "%d,%ld,%s\n",
                n,
                comparisons,
                duplicate ? "Yes" : "No");

        free(a);
    }

    fclose(fp);

    printf("\nConclusion:\n");
    printf("As the array size increases, the number of comparisons grows approximately proportional to n^2.\n");
    printf("Therefore, the naive element uniqueness algorithm has O(n^2) time complexity.\n");

    FILE *py = fopen("plot_q6.py", "w");

    if(py == NULL)
    {
        printf("Error creating Python script.\n");
        return 1;
    }

    fprintf(py,"import pandas as pd\n");
    fprintf(py,"import matplotlib.pyplot as plt\n\n");

    fprintf(py,"df = pd.read_csv('unique_data.csv')\n\n");

    fprintf(py,"plt.figure(figsize=(10,6))\n");
    fprintf(py,"plt.plot(df['ArraySize'], df['Comparisons'], marker='o', linewidth=2)\n");
    fprintf(py,"plt.xlabel('Array Size (n)')\n");
    fprintf(py,"plt.ylabel('Number of Comparisons')\n");
    fprintf(py,"plt.title('Element Uniqueness (Naive O(n^2) Method)')\n");
    fprintf(py,"plt.grid(True)\n");
    fprintf(py,"plt.tight_layout()\n");
    fprintf(py,"plt.savefig('Q6_ElementUniqueness.png', dpi=300)\n");
    fprintf(py,"plt.show()\n");

    fclose(py);

    printf("\nGenerating graph...\n");

    system("python plot_q6.py");

    printf("Graph saved as Q6_ElementUniqueness.png\n");

    return 0;
}
