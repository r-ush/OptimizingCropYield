#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

//functions used
int MainMenu();
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
int knapsack(int i, int yield, int k_budget, int k_area);

int main()
{
    cout << "WELCOME TO THE FARMEASY PROJECT\n";
    MainMenu();
    return 0;
}

int MainMenu()
{
    int option;
    cout << "1. New Farmer\n"
         << "2. Existing Farmer\n"
         << "3. Access Farmer Database\n"
         << "4. Access Crop Database\n"
         << "5. Edit Crop Database\n"
         << "6. Exit\n";
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
            cout << "Welcome, " << Fname << "!\n";
            //file << Fname << endl; //File Handling test
            int budget, area;
            cout << "Please Enter the Expenditure Budget: ";
            cin >> budget;
            cout << "Please Enter the Area of Land to be used: ";
            cin >> area;

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            //counting the number of crops
            file.seekg(0, ios::beg);
            ::count = -1;
            while(getline(file, line))
            {
                ::count++;
            }
            cout << ::count << endl;
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
            cout << "OptimizedYield = " << OptimizedYield << endl;

            //OptimizedYield = knapsack()[0];
            file.open("FarmerDatabase.csv", ios::app | ios::out | ios::in);
            file << ", " << Fname << " , " << budget << " , " << area << " , " << OptimizedYield << endl;
            file.close();
            
            cout << "//TODO visualisation" << endl;
            cout << "Thankyou!" << endl;
            break;
        }
    case 2:
        {
            //TODO
            cout << "//TODO\nReturning to Main Menu\n\n";
            MainMenu();
            break;
        }
    case 3:
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
            cout << "Returning to Main Menu\n";
            MainMenu();
            break;
        }
    case 4:
        {
            fstream file;
            string line;
            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            file.seekg(0, ios::beg);
            cout << "";
            while(getline(file, line))
            {
                cout << line << endl;
            }
            cout << "";
            file.close();

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            //counting the number of crops
            file.seekg(0, ios::beg);
            int count = -1;
            while(getline(file, line))
            {
                count++;
            }
            cout << count << endl;
            file.close();

            file.open("CropDatabase.csv", ios::app | ios::out | ios::in);
            struct CropData *Crop;
            Crop = new CropData [count];
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
                cout << Crop[i].name << endl;
                stringstream c1(row[1]);
                c1 >> Crop[i].capital;
                cout << Crop[i].capital << endl;
                stringstream c2(row[2]);
                c2 >> Crop[i].area;
                cout << Crop[i].area << endl;
                stringstream c3(row[3]);
                c3 >> Crop[i].yield;
                cout << Crop[i].yield << endl;
                i++;
            }
            cout << "Returning to Main Menu\n";
            MainMenu();
            break;
        }
    case 5:
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
            break;
        }
    case 6:
        {
            cout << "Thankyou!\n";
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
