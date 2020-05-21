#include <stdio.h>
#include <stdlib.h>
//#include<graphics.h>

#define nitems 6

typedef struct
{
    char name[100];
    double yield;
    double production;
    double area;
}itemconstraints;

itemconstraints items[nitems];
int n=nitems;
int *count;
int *best;
double best_yield;
int knapsack(int i, double yield, double production, double area);


int main()
{
    int question;
    printf("Enter the code of your problem: \n");
    scanf("%d",&question);

    switch(question){
        case 1:
            printf("1");
            FILE* file = fopen("agriculture.csv", "r");
            size_t c = 0;
            for (c=0 ; c < sizeof(items)/sizeof(items[0]); ++c)
            {
                int got = fscanf(file, "%[^,],%lf,%lf,%lf\n", &items[c].name, &items[c].yield, &items[c].production, &items[c].area);
                if (got != 4) break;
            }
            fclose(file);
            break;

        case 2:
            printf("2");
            break;

        case 3:
            printf("3");
            break;

        default:
            printf("Error! operator is not correct");
    }



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
    free(count);
    free(best);
    return 0;
}

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



