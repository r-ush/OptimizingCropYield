#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>
#include <math.h>
//#include <bprinter/table_printer.h>
using namespace std;

//functions used
int MainMenu();
int knapsack(int i, int yield, int k_budget, int k_area);
int visualisation();
//full declaration of struct because forward declaration doesn't work while allocating memory with "new"
struct CropData
{
    string name;
    int capital;
    int area;
    int yield;
};

struct CropData *Crop;
int count;
int *cropcount;
int *best;
int  OptimizedYield;
char vis[100];

int main()
{
    cout << "\nWELCOME TO THE FARMEASY PROJECT\n\n";
    MainMenu();
    return 0;
}

int MainMenu()
{
    int option;
    cout << "1. Plan a Farm\n"
        // << "2. Existing Farmer\n"
         << "2. Access Farmer Database\n"
         << "3. Access Crop Database\n"
         << "4. Add to Crop Database\n"
         << "5. Exit\n\n";
    //
    cout << "Enter Option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        {
            fstream file;
            string Fname, line;
            cout << "Enter Farmer Name: ";
            cin >> Fname;
            cout << "\nWelcome, " << Fname << "!\n\n";
            //file << Fname << endl; //File Handling test
            int budget, area;
            cout << "Please Enter the Expenditure Budget (in Rupees): ";
            cin >> budget;
            cout << "\nPlease Enter the Area of Land to be used (in meter square): ";
            cin >> area;

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            //counting the number of crops
            file.seekg(0, ios::beg);
            ::count = -1;
            while(getline(file, line))
            {
                ::count++;
            }
            cout << "\nTotal Number of crops in Database: " << ::count << "\n" << endl;
            file.close();

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);

            Crop = new CropData [::count];
            file.seekg(0, ios::beg);

            vector<string> row;
            string word, temp;
            int i = 0;
            getline(file, line);
            while(file >> temp)
            {
                row.clear();
                getline(file, line);
                stringstream s(line);
                while(getline(s, word, ','))
                {
                    row.push_back(word);
                }

                Crop[i].name = row[0];
                //cout << Crop[i].name << endl;
                stringstream c1(row[1]); //because stio was not working
                c1 >> Crop[i].capital;
                //cout << Crop[i].capital << endl;
                stringstream c2(row[2]);
                c2 >> Crop[i].area;
                //cout << Crop[i].area << endl;
                stringstream c3(row[3]);
                c3 >> Crop[i].yield;
                //cout << 2*Crop[i].yield << endl;
                i++;
            }
            file.close();

            cropcount = new int [::count];
            best = new int [::count];
            OptimizedYield = 0;

            knapsack(0, 0, budget, area);
            cout << "OptimizedYield = Rs. " << OptimizedYield << endl;

            ///printing out cropwise result
            int j = 0;
            cout << "Crop Count" << "\t" << "Crop Name" << "\t" << "Area" << "\t\t" << "Cost" << endl;
            for (j = 0; j < ::count ; j++)
            {
                cout << best[j] << "\t\t" << Crop[j].name << "\t\t" << Crop[j].area*best[j] << "\t\t" << Crop[j].capital*best[j] << endl;
            }

            //OptimizedYield = knapsack()[0];
            file.open("FarmerDatabase.csv", ios::app | ios::out | ios::in);
            file << ", " << Fname << " , " << budget << " , " << area << " , " << OptimizedYield << endl;
            file.close();
            cout << "\n";
            //cout << "//TODO visualisation" << endl;
            visualisation();
            cout << "\nThankyou!\n" << endl;
            MainMenu();
            break;
        }
    // case 2:
    //     {
    //         //TODO
    //         cout << "//TODO\nReturning to Main Menu\n\n";
    //         MainMenu();
    //         break;
    //     }
    case 2:
        {
            fstream file;
            string line;
            file.open("FarmerDatabase.csv", ios::app | ios::out | ios::in);
            file.seekg(0, ios::beg);
            cout << "";
            while(getline(file, line))
            {
                cout << line << endl;
            }
            cout << "";
            file.close();
            cout << "Returning to Main Menu\n\n";
            MainMenu();
            break;
        }
    case 3:
        {
            fstream file;
            string line;
            // file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            // file.seekg(0, ios::beg);
            // cout << "";
            // while(getline(file, line))
            // {
            //     cout << line << endl;
            // }
            // cout << "";
            // file.close();

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            //counting the number of crops
            file.seekg(0, ios::beg);
            int count = -1;
            while(getline(file, line))
            {
                count++;
            }
            cout << "\nTotal Number of crops in Database: " << count << "\n" << endl;
            file.close();

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            struct CropData *Crop;
            Crop = new CropData [count];
            file.seekg(0, ios::beg);

            vector<string> row;
            string word, temp;
            int i = 0;
            getline(file, line);
            cout << "Crop Name\tCapital Required\tArea Planted\tYield" << endl;
            while(file >> temp)
            {
                row.clear();
                getline(file, line);
                stringstream s(line);
                while(getline(s, word, ','))
                {
                    row.push_back(word);
                }

                Crop[i].name = row[0];
                //cout << Crop[i].name << endl;
                stringstream c1(row[1]);
                c1 >> Crop[i].capital;
                //cout << Crop[i].capital << endl;
                stringstream c2(row[2]);
                c2 >> Crop[i].area;
                //cout << Crop[i].area << endl;
                stringstream c3(row[3]);
                c3 >> Crop[i].yield;
                cout << Crop[i].name << "\t\t" << Crop[i].capital << "\t\t\t" << Crop[i].area << "\t\t" << Crop[i].yield << endl;
                i++;
            }

            cout << "\nReturning to Main Menu\n\n";
            MainMenu();
            break;
        }
    case 4:
        {
            fstream file;
            cout << "Please Enter Details of the New Crop\n";
            string CropName;
            cout << "Crop Name: ";
            cin >> CropName;
            int capital, area, yield;
            cout << "Capital Required: ";
            cin >> capital;
            cout << "Area of land required: ";
            cin >> area;
            cout << "Yield Obtained: ";
            cin >> yield;
            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            file << ", " << CropName << " , " << capital << " , " << area << " , " << yield << endl;
            file.close();
            cout << "\nReturning to Main Menu\n\n";
            MainMenu();
            break;
        }
    case 5:
        {
            cout << "\nThankyou!\n";
            break;
        }
    default:
        {
            cout << "\nPlease Enter a Valid Option\n\n";
            MainMenu();
            break;
        }
    }
}

int knapsack(int i, int yield, int k_budget, int k_area)
{
    int j, m1, m2, m;
    if (i==::count)
    {
        if (yield > OptimizedYield)
        {
            OptimizedYield = yield;
            for (j = 0; j < ::count ; j++)
            {
                best[j] = cropcount[j];
            }
        }
    return 0;
    }
    m1 = k_budget / Crop[i].capital;
    m2 = k_area / Crop[i].area;

    m = m1<m2 ? m1:m2;

    for (cropcount[i] = m; cropcount[i] >= 0; cropcount[i]--)
    {
        knapsack(i+1, (yield+(cropcount[i]*Crop[i].yield)), (k_budget-(cropcount[i]*Crop[i].capital)), (k_area-(cropcount[i]*Crop[i].area)));
    }
}

int visualisation()
{
    cout << "A visual representation:\n\n";
    int i = 0, j=0, k=0, tbp_c = 0, total = 0, exp = 0;
    string *tobeplanted;
    int *tbp_l;
    char keys[5] = {'#', '*', '@', '^', '&'};
    for (i = 0; i < ::count ; i++)
    {
        if (::best[i] > 0)
        {
            tbp_c++;
            total += Crop[i].area*best[i];
            exp += Crop[i].capital*best[i];
        }
    }
    cout << "Total Area Planted: "<< total << endl;
    cout << "Total Expenditure: "<< exp << endl;
    //tobeplanted = new string[tbp_c];
    //tbp_l = new int [tbp_c];
    cout << "Keys: \n";
    int l = 0;
    for (i = 0; i < ::count ; i++)
    {

        if (::best[i] > 0)
        {
            double perf = ((float(Crop[i].area)*float(best[i]))/float(total))*100;
            int per = floor(perf);
            cout << Crop[i].name << " : " << keys[k] << "  " << per << "%" << endl;
            int m = 0;
            for (m; m < per; m++)
            {
                vis[l+m] = keys[k];
            }
            k++;
            l+=per;
        }
    }
    cout << "\n";
    int p = 0, q = 0, r = 0;
    for (p = 0; p < 10 ; p++)
    {
        cout << "\t";
        for (q = 0; q < 10; q++)
        {
            cout << vis[r];
            r++;
        }
        cout << "\n";
    }
}
