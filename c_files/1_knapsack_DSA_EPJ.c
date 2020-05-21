#include <stdio.h>
#include <stdlib.h>
#include<graphics.h>

typedef struct
{
    char *name;
    double value;
    double weight;
    double volume;
}itemconstraints;

itemconstraints items[] = {{"Sapphire", 3000.0, 3, 5}, {"Diamond", 1800.0, 1, 3}, {"Gold", 2500.0, 2, 4}, {"Silver", 2000.0, 4, 3}, {"Ruby", 1500.0, 3, 4}};

int n = sizeof(items)/sizeof(itemconstraints);
int *count;
int *best;
double best_value;
int knapsack(int i, double value, double weight, double volume)
{
    int j, m1, m2, m;
    if (i==n)
    {
        if (value>best_value)
            {
                best_value=value;
                for (j=0;j<n;j++)
                {
                    best[j]=count[j];
                }
            }
    return 0;
    }
    m1=weight/items[i].weight;
    m2=volume/items[i].volume;
    m=m1<m2?m1:m2;
    for (count[i]=m; count[i]>= 0; count[i]--)
    {
            knapsack(i+1, (value+(count[i]*items[i].value)), (weight-(count[i]*items[i].weight)), (volume-(count[i]*items[i].volume)));
    }
}

int main()
{

    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL);

//    int n_items, k=0, m=0;
//    printf("Enter the number of constraints: ");
//    scanf("%d", n_items);
//    itemconstraints items[n_items];
//    for (k=0;k<n_items;k++)
//    {
//        printf("Enter Details of Gem %d", k+1);
//        for (m=0;m<4;m++);
//        printf("Enter Gem name: ");
//        scanf("%s", &items[k].name);
//        printf("Enter it's Value: ");
//        scanf("%d", &items[k].value);
//        printf("Enter it's weight: ");
//        scanf("%d", items[k].weight);
//        printf("Enter it's Volume: ");
//        scanf("%f", items[k].volume);
//    }

    count= malloc(n*sizeof(int));
    best= malloc(n*sizeof(int));
    best_value=0;
    float wt,vol;
    printf("Enter the maximum weight that can be carried: ");
    scanf("%f",&wt);
    printf("Enter the maximum volume of the bag: ");
    scanf("%f",&vol);
    knapsack(0, 0.0, wt, vol);
    int i;
    for (i=0;i<n;i++)
    {
        printf("%d %s\n", best[i], items[i].name);
        pieslice(300, 300, 0, 120, 150);
    }
    printf("Best Value: %.0f\n", best_value);
    free(count);
    free(best);

    // pieslice function
    //pieslice(300, 300, 0, 120, 150);

    getch();

    closegraph();

    //to run the program  gcc 1_knapsack_DSA_EPJ.c -o 1_knapsack -lgraph
    // ./sample

    return 0;
}
