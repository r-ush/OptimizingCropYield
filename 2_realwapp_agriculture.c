#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    double yield;
    double production;
    double area;
}itemconstraints;

itemconstraints items[] = {{"Rice", 1808, 72.3, 40.0}, {"Wheat", 2577 , 68.8, 26.7}, {"Maize", 1637, 59.3, 25.7}, {"Bajra", 779, 27.5, 19.6},{"Miscellaneous Cereals", 1071, 45.7, 24.0}};

int n = sizeof(items)/sizeof(itemconstraints);
int *count;
int *best;
double best_yield;
int knapsack(int i, double yield, double production, double area)
{
    int j, m1, m2, m;
    if (i==n)
    {
        if (yield>best_yield)
            {
                best_yield=yield;
                for (j=0;j<n;j++)
                {
                    best[j]=count[j];
                }
            }
    return 0;
    }
    m1=production/items[i].production;
    m2=area/items[i].area;
    m=m1<m2?m1:m2;
    for (count[i]=m; count[i]>= 0; count[i]--)
    {
            knapsack(i+1, (yield+(count[i]*items[i].yield)), (production-(count[i]*items[i].production)), (area-(count[i]*items[i].area)));
    }
}

int main()
{
//    int n_crops
//    printf("Enter the number of crops: ");
//    scanf("%d", n_crops);
//

    count= malloc(n*sizeof(int));
    best= malloc(n*sizeof(int));
    best_yield=0;
    float wt,vol;
    printf("Enter the maximum production size: ");
    scanf("%f",&wt);
    printf("Enter the maximum area of the field: ");
    scanf("%f",&vol);
    knapsack(0, 0.0, wt, vol);
    int i;
    for (i=0;i<n;i++)
    {
        printf("%d %s\n", best[i], items[i].name);
    }
    printf("Best yield: %.0f\n", best_yield);
    printf("%d", n);
    free(count);
    free(best);
    return 0;
}




