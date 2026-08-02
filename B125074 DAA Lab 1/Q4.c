#include <stdio.h>
#include <stdlib.h>

long moves;

void hanoi(int n, char from, char to, char aux)
{
    if(n==0) return;
    hanoi(n-1, from, aux, to);
    moves++;
    hanoi(n-1, aux, to, from);
}

int main()
{
    FILE *fp=fopen("hanoi_data.csv","w");
    fprintf(fp,"n,moves\n");

    for(int n=1;n<=20;n++){
        moves=0;
        hanoi(n,'A','C','B');
        fprintf(fp,"%d,%ld\n",n,moves);
    }
    fclose(fp);

    printf("\nCSV file created : hanoi_data.csv\n");

    FILE *py=fopen("plot_q4.py","w");

    fprintf(py,"import pandas as pd\n");
    fprintf(py,"import matplotlib.pyplot as plt\n");
    fprintf(py,"df=pd.read_csv('hanoi_data.csv')\n");
    fprintf(py,"fig,(ax1,ax2)=plt.subplots(1,2,figsize=(10,4))\n");
    fprintf(py,"ax1.plot(df['n'],df['moves'],marker='o')\n");
    fprintf(py,"ax1.set_xlabel('Number of discs (n)')\n");
    fprintf(py,"ax1.set_ylabel('Number of moves')\n");
    fprintf(py,"ax1.set_title('Linear scale')\n");
    fprintf(py,"ax2.plot(df['n'],df['moves'],marker='o')\n");
    fprintf(py,"ax2.set_yscale('log')\n");
    fprintf(py,"ax2.set_xlabel('Number of discs (n)')\n");
    fprintf(py,"ax2.set_ylabel('Number of moves (log scale)')\n");
    fprintf(py,"ax2.set_title('Log scale (straight line -> exponential growth)')\n");
    fprintf(py,"plt.tight_layout()\n");
    fprintf(py,"plt.savefig('Q4_Growth.png')\n");
    fprintf(py,"plt.show()\n");

    fclose(py);

    system("python3 plot_q4.py");

    printf("\nGraph saved as Q4_Growth.png\n");

    return 0;
}