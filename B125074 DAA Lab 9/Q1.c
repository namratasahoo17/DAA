#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    double value;
    double weight;
    double decay;
    int used;
} Item;


int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *items = malloc(n * sizeof(Item));

    if (items == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter value, weight and decay rate for each item:\n");

    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        items[i].used = 0;

        printf("Item %d: ", i + 1);
        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    double remaining = W;
    double time = 0.0;
    double totalValue = 0.0;

    printf("\nSelected items:\n");

    while (remaining > 0)
    {
        int best = -1;
        double bestDensity = -1e100;

        /*
           Find the item with the highest
           current effective density.
        */

        for (int i = 0; i < n; i++)
        {
            if (items[i].used)
                continue;

            double density =
                items[i].value / items[i].weight
                - items[i].decay * time;

            if (density > bestDensity)
            {
                bestDensity = density;
                best = i;
            }
        }

        /*
           No item is available.
        */

        if (best == -1)
            break;

        /*
           Determine how much of the item
           we can take.
        */

        double amount;

        if (items[best].weight <= remaining)
        {
            /*
               Take the whole item.
            */
            amount = items[best].weight;
            items[best].used = 1;
        }
        else
        {
            /*
               Take only the fraction that fits.
            */
            amount = remaining;
            items[best].used = 1;
        }

        /*
           Value obtained from this amount.
        */

        double gainedValue =
            amount * bestDensity;

        totalValue += gainedValue;

        /*
           Update capacity and time.
        */

        remaining -= amount;
        time += amount;

        double fraction =
            amount / items[best].weight;

        printf("Item %d: fraction = %.2f, "
               "amount = %.2f, "
               "density = %.4f, "
               "value gained = %.4f\n",
               items[best].id,
               fraction,
               amount,
               bestDensity,
               gainedValue);
    }

    printf("\nTotal value = %.4f\n", totalValue);
    printf("Used capacity = %.4f\n", W - remaining);

    free(items);

    return 0;
}