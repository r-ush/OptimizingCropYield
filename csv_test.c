#include <stdio.h>

typedef struct
{
    char name[100];
    double yield;
    double production;
    double area;
}itemconstraints;


int main()
{
    FILE* my_file = fopen("agriculture.csv", "r");
    itemconstraints records[100];
    size_t count = 0;
    for (; count < sizeof(records)/sizeof(records[0]); ++count)
    {
        int got = fscanf(my_file, "%[^,],%lf,%lf,%lf\n", &records[count].name, &records[count].yield, &records[count].production, &records[count].area);
        if (got != 4) break;
    }
//    while (fscanf(my_file, " %[^,],%lf,%lf,%lf", &records[count].name, &records[count].yield, &records[count].production, &records[count].area) == 1)
        //{count++;}
    int i=0;
    for (i=0;i<5;i++)
    {
        printf("%s %lf, %lf\n", records[i].name, records[i].yield, records[i].area);
    }
    double val;
    char* buf[100];
//    while (fscanf(my_file,"%s,%*s,%*s,%lf",buf, val)==1)
//        printf("%s\n", buf);
//    fclose(my_file);
}
//sizeof(records)/sizeof(records[0)
