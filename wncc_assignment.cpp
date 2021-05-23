//Greedy Algorithm has been used
//Source: Competitive Programmer's Handbook by Antti Laaksonen

#include <iostream>
#include <fstream>
#include <stdlib.h>    //for malloc

using namespace std;

int opening_time; //to find the opening time
int NoOfGws;

struct Groundwork {
    int startTime, endTime, duration;
}obj_gw;

struct Available_Groundworks {
    int n; //no. of groundworks a student has signed up for
    Groundwork* gwdetails = (Groundwork*)malloc(sizeof(obj_gw)*NoOfGws);  
    void freespace()
    {
        free(gwdetails);
    } 
}obj_avl_gw;

Available_Groundworks gw;

Available_Groundworks* initialize(int start_time[], int duration[], int n)
{  
    gw.n = n;
    opening_time = start_time[0];
    for(int i=0; i<n; i++)
    {
        gw.gwdetails[i].startTime = start_time[i];
        gw.gwdetails[i].duration = duration[i];
        gw.gwdetails[i].endTime = (start_time[i] + duration[i])%24;
    }
    return &gw;
}

int CalculateMaxGroundworks(Available_Groundworks* ptr)  //Returns maximum number of groundworks the student can attend - without overlap
{
    int j=0, count=1; //we take the first event because it ends at earliest
    cout << ptr->gwdetails[j].startTime << "  " << ptr->gwdetails[j].endTime << endl;
    for(int i=1; i<ptr->n; i++)
    {
        if(ptr->gwdetails[i].startTime >= ptr->gwdetails[j].endTime)
        {
            j = i;
            count ++;
            cout << ptr->gwdetails[j].startTime << "  " << ptr->gwdetails[j].endTime << endl;
        }
    }
    return count;
}

int main()
{
    ifstream file("Schedule.txt");
    int countlines = 0;
    string line;
    if(file.is_open())
    {
        while(getline(file, line))
        {
            countlines++;
        }
    }
    else
        cout << "Can't open file!";
    file.close();
    int starttime[countlines], duration[countlines], endtime[countlines], i=0;
    char gwname[4];
    ifstream file1("Schedule.txt");
    while(!file1.eof())
    {
        file1 >> gwname;
        file1 >> starttime[i];
        file1 >> duration[i];
        i++;
    }
    file1.close();

    NoOfGws = countlines;

    for(int i=0; i<countlines; i++)
        endtime[i] = (starttime[i]+duration[i])%24;

    for(int i=0; i<countlines; i++)
    {
        for(int j=0; j<countlines-i-1; j++)
        {
            if(endtime[j] > endtime[j+1])
            {
                int temp0 = endtime[j+1];
                int temp1 = duration[j+1];
                int temp2 = starttime[j+1];
                duration[j+1] = duration[j];
                starttime[j+1] = starttime[j];
                endtime[j+1] = endtime[j];
                endtime[j] = temp0;
                duration[j] = temp1;
                starttime[j] = temp2;
            }
        }
    }

    Available_Groundworks* obj = initialize(starttime, duration, countlines);
    int maxnumber = CalculateMaxGroundworks(obj);
    cout << "Maximum number of groundworks that can be attended: " << maxnumber;
    obj_avl_gw.freespace();
 }

