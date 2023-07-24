#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

struct Workshop
{
    int start_time;
    int duration;
    int end_time;
    
    bool operator<(const Workshop &right_start)
    {
        return this->end_time < right_start.end_time;
    }
};

struct Available_Workshops
{
    int num;
    Workshop* arr;
    //vector<Workshop> arr;
    Available_Workshops():num(0),arr(nullptr){}
};

Available_Workshops* initialize(int* &start, int* &dur, int n)
{
    Available_Workshops* obj = new Available_Workshops;
    obj->num = n;
    
    Workshop* shops = new Workshop[n];
    //vector<Workshop> shops(n);
    for(int i = 0; i < n; i++)
    {
        shops[i].start_time = start[i];
        shops[i].duration = dur[i];
        shops[i].end_time = start[i] + dur[i];
    }
    sort(shops, shops + n);
    //sort(shops.begin(), shops.end());
    
    obj->arr = shops;
    return obj;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int count = 1;
    int curr = 0;
    
    for(int i = 0; i < ptr->num-1; i++)
    {
        if(ptr->arr[curr].end_time <= ptr->arr[i+1].start_time)
        {
            count++;
            curr = i+1;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    std::ifstream file("input/Medium_AttendingWorkshops.txt");
    if(file.is_open())
    {
        int n; // number of workshops
        file >> n;
        // create arrays of unknown size n
        int* start_time = new int[n];
        int* duration = new int[n];

        for(int i=0; i < n; i++){
            file >> start_time[i];
        }
        for(int i = 0; i < n; i++){
            file >> duration[i];
        }

        Available_Workshops * ptr;
        ptr = initialize(start_time,duration, n);
        cout << CalculateMaxWorkshops(ptr) << endl;
    }
    file.close();

    return 0;
}