#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    const int N = 100000;
    const double biasP = 0.7;

    int headsFair = 0;
    int headsBiased = 0;

    FILE *fp = fopen("coin_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }

    fprintf(fp, "Tosses,FairCoin,BiasedCoin\n");

    for (int i = 1; i <= N; i++)
    {
        double r1 = (double)rand() / RAND_MAX;
        if (r1 < 0.5)
            headsFair++;

        double r2 = (double)rand() / RAND_MAX;
        if (r2 < biasP)
            headsBiased++;

        if (i % 1000 == 0)
        {
            fprintf(fp, "%d,%.6f,%.6f\n",
                    i,
                    (double)headsFair / i,
                    (double)headsBiased / i);
        }
    }

    fclose(fp);

    printf("\n========== FAIR COIN ==========\n");
    printf("Total Tosses : %d\n", N);
    printf("Heads        : %d\n", headsFair);
    printf("Probability  : %.6f\n", (double)headsFair / N);

    printf("\n========= BIASED COIN =========\n");
    printf("Total Tosses : %d\n", N);
    printf("Heads        : %d\n", headsBiased);
    printf("Probability  : %.6f\n", (double)headsBiased / N);
    printf("Expected     : %.2f\n", biasP);

    printf("\nCSV file created successfully: coin_data.csv\n");

    FILE *py = fopen("plot_q2.py", "w");

    if (py == NULL)
    {
        printf("Error creating Python script.\n");
        return 1;
    }

    fprintf(py, "import pandas as pd\n");
    fprintf(py, "import matplotlib.pyplot as plt\n\n");

    fprintf(py, "df = pd.read_csv('coin_data.csv')\n\n");

    fprintf(py, "plt.figure(figsize=(10,6))\n");
    fprintf(py, "plt.plot(df['Tosses'], df['FairCoin'], label='Fair Coin', linewidth=2)\n");
    fprintf(py, "plt.plot(df['Tosses'], df['BiasedCoin'], label='Biased Coin (p=0.7)', linewidth=2)\n");
    fprintf(py, "plt.axhline(y=0.5, color='green', linestyle='--', label='Fair = 0.5')\n");
    fprintf(py, "plt.axhline(y=0.7, color='red', linestyle='--', label='Bias = 0.7')\n");
    fprintf(py, "plt.xlabel('Number of Tosses')\n");
    fprintf(py, "plt.ylabel('Probability of Head')\n");
    fprintf(py, "plt.title('Fair vs Biased Coin Toss Simulation')\n");
    fprintf(py, "plt.grid(True)\n");
    fprintf(py, "plt.legend()\n");
    fprintf(py, "plt.tight_layout()\n");
    fprintf(py, "plt.savefig('Q2_CoinToss.png', dpi=300)\n");
    fprintf(py, "plt.show()\n");

    fclose(py);

    printf("Generating graph...\n");

    system("python plot_q2.py");

    printf("Graph saved as Q2_CoinToss.png\n");

    return 0;
}