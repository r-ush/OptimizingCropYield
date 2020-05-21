#include<stdio.h>
#include<stdlib.h>
typedef struct { char
*name; double
calorie; double
carbohydrates; double
fibers; }
itemcontraints;
itemcontraints items[] = {
{"asparagus", 25.0, 1, 8},
{"carrot", 30.0 , 2, 8},
{"sweet potato", 100, 8, 16},
{"mushrooms", 20, 1, 4},
{"onion", 45, 4, 12},
};
int n = sizeof (items) / sizeof
(itemcontraints); int *count; int *best;
double best_calorie;
void knapsack (int i, double calorie, double carbohydrates, double fibers)
{ int j, m1, m2, m; if (i == n) { if (calorie >best_calorie) { best_calorie =
calorie; for (j = 0; j < n; j++) {
best[j] = count[j];
}
}
return;
}
m1 = carbohydrates / items[i].carbohydrates;
m2 = fibers / items[i].fibers;
m = m1 <m2 ?m1 : m2; for (count[i] =
m; count[i] >= 0; count[i]--) {
knapsack( i
+ 1,
calorie + count[i] * items[i].calorie,
carbohydrates - count[i] * items[i].carbohydrates,
fibers - count[i] * items[i].fibers
);
} } int main () { count = malloc(n
* sizeof (int)); best = malloc(n *
sizeof (int)); best_calorie = 0;
float carbo,fb;
printf("carbohydrates content: "); scanf("%f",&carbo);
printf("dietary fibers content :");
scanf("%f",&fb); knapsack(0, 0.0,
carbo, fb);
int i; for (i = 0; i< n; i++) {
printf("%d %s\n", best[i], items[i].name);
}
printf("maximum calories: %.0f\n", best_calorie);
free(count); free(best);
return 0;
}
