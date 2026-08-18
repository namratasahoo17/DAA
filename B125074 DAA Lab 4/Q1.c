//Application of sorting-I: Assume that we are given n pairs of items as input, where the first item is a number and the second item is one of three colours (red, blue, or yellow). Further assume that the items are sorted by number. Give an O(n) algorithm to sort the items by colour (all reds before all blues before all yellows) such that the numbers for identical colours stay sorted. By choosing the proper input representation, write a program in C to validate your algorithm.

/* ALGORITHM SortByColour(items, n)

    Create three empty lists:
        RED
        BLUE
        YELLOW

    FOR i = 1 TO n DO

        IF items[i].colour = RED THEN
            Add items[i] to RED

        ELSE IF items[i].colour = BLUE THEN
            Add items[i] to BLUE

        ELSE IF items[i].colour = YELLOW THEN
            Add items[i] to YELLOW

    END FOR

    OUTPUT RED
    OUTPUT BLUE
    OUTPUT YELLOW

END ALGORITHM */

#include <stdio.h>
#include <string.h>

struct Item
{
    int number;
    char color[10];
};

int main()
{
    int n;

    printf("========================================\n");
    printf("       SORTING ITEMS BY COLOUR\n");
    printf("========================================\n");

    printf("\nEnter number of items: ");
    scanf("%d", &n);

    struct Item items[n];

    printf("\nEnter %d items in sorted order by number:\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("\nItem %d number: ", i + 1);
        scanf("%d", &items[i].number);

        printf("Item %d colour (red/blue/yellow): ", i + 1);
        scanf("%s", items[i].color);
    }

// Arrays for the three colours.

    struct Item red[n];
    struct Item blue[n];
    struct Item yellow[n];

    int redCount = 0;
    int blueCount = 0;
    int yellowCount = 0;

/*
    O(n) sorting by colour.

    Since the input is already sorted by number, we simply put each item into its colour group.
*/

for (int i = 0; i < n; i++)
    {
        if (strcmp(items[i].color, "red") == 0)
        {
            red[redCount] = items[i];
            redCount++;
        }
        else if (strcmp(items[i].color, "blue") == 0)
        {
            blue[blueCount] = items[i];
            blueCount++;
        }
        else if (strcmp(items[i].color, "yellow") == 0)
        {
            yellow[yellowCount] = items[i];
            yellowCount++;
        }
        else
        {
            printf("\nInvalid colour: %s\n",
                   items[i].color);
            return 0;
        }
    }

// Display original input.

    printf("\n========================================\n");
    printf("              INPUT\n");
    printf("========================================\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d %s\n",
               items[i].number,
               items[i].color);
    }
// Display result.

    printf("\n========================================\n");
    printf("          SORTED BY COLOUR\n");
    printf("========================================\n");

    printf("\nRED:\n");

    for (int i = 0; i < redCount; i++)
    {
        printf("%d red\n", red[i].number);
    }

    printf("\nBLUE:\n");

    for (int i = 0; i < blueCount; i++)
    {
        printf("%d blue\n", blue[i].number);
    }

    printf("\nYELLOW:\n");

    for (int i = 0; i < yellowCount; i++)
    {
        printf("%d yellow\n", yellow[i].number);
    }

// Display the final combined list.

 printf("\n========================================\n");
    printf("          FINAL OUTPUT\n");
    printf("========================================\n");

    for (int i = 0; i < redCount; i++)
    {
        printf("(%d, red)\n", red[i].number);
    }

    for (int i = 0; i < blueCount; i++)
    {
        printf("(%d, blue)\n", blue[i].number);
    }

    for (int i = 0; i < yellowCount; i++)
    {
        printf("(%d, yellow)\n", yellow[i].number);
    }

    /*
       Analysis.
    */

    printf("\n========================================\n");
    printf("             ANALYSIS\n");
    printf("========================================\n");

    printf("The input is already sorted by number.\n");
    printf("Each item is visited exactly once.\n");
    printf("Items are placed into one of three colour groups.\n");
    printf("The order within each colour is preserved.\n");

    printf("\nTime Complexity: O(n)\n");
    printf("Space Complexity: O(n)\n");

    return 0;
}