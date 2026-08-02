#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    const char *functions[]={
        "1",
        "log2(n)",
        "12sqrt(n)",
        "n^0.51",
        "n",
        "3n",
        "nlog2(n)",
        "nlog2(n^2)",
        "n^2-324",
        "n^2+6n",
        "100n^2",
        "n^3",
        "2^(32n)"
    };
    /* Arbitrary increasing values just for plotting the order */
    double order[]={
        1,2,3,4,5,6,7,8,9,10,11,12,13
    };
    int n=13;
    printf("\nIncreasing Order of Growth\n\n");
    for(int i=0;i<n;i++)
        printf("%2d. %s\n",i+1,functions[i]);
    fp=fopen("growth_data.csv","w");
    fprintf(fp,"Function,Order\n");
    for(int i=0;i<n;i++)
        fprintf(fp,"%s,%lf\n",functions[i],order[i]);
    fclose(fp);
    printf("\nCSV file created : growth_data.csv\n");
    FILE *py=fopen("plot_q1.py","w");
    fprintf(py,"import pandas as pd\n");
    fprintf(py,"import matplotlib.pyplot as plt\n");
    fprintf(py,"df=pd.read_csv('growth_data.csv')\n");
    fprintf(py,"plt.figure(figsize=(10,6))\n");
    fprintf(py,"plt.barh(df['Function'],df['Order'])\n");
    fprintf(py,"plt.title('Increasing Order of Growth')\n");
    fprintf(py,"plt.xlabel('Relative Growth Rank')\n");
    fprintf(py,"plt.tight_layout()\n");
    fprintf(py,"plt.savefig('Q1_Growth.png')\n");
    fprintf(py,"plt.show()\n");
    fclose(py);
    system("python plot_q1.py");
    printf("\nGraph saved as Q1_Growth.png\n");
    return 0;
}
