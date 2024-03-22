/***********************************************************************
Matr.-Nr:                     3085596
Nachname/Surname:             Haque
Vorname/Given name:           Md Anamul
Uni-Email:                    md.haque.696@stud.uni-due.de
Studiengang/Course of studis: ISE(Software Engineering)
***********************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// //Example Program Run 1 for 10 days and 12 quarter hours
// const int days_in_year = 10;  
// const int interval_quater_hour = 12; 

// Example Program Run 2 for 365days and 96 quarter hours
const int days_in_year = 365;  
const int interval_quater_hour = 96;  

// 1.(A3.1) Define a enumeration structure called use
enum Use 
{ 
    monday,  
    tuesday, 
    wednesday, 
    thursday, 
    friday, 
    saturday, 
    sunday,  
    once, 
    daily, 
    mo_fr, 
    sa_su
};

// 2.(A3.1)
ostream& operator<<(ostream& out, const Use& use_day) 
{
    switch (use_day) 
    {
        case monday:    out << "Monday";             break;
        case tuesday:   out << "Tuesday";            break;
        case wednesday: out << "Wednesday";          break;
        case thursday:  out << "Thursday";           break;
        case friday:    out << "Friday";             break;
        case saturday:  out << "Saturday";           break;
        case sunday:    out << "Sunday";             break;
        case once:      out << "once";               break;
        case daily:     out << "daily";              break;
        case mo_fr:     out << "Monday to Friday";   break;
        case sa_su:     out << "Saturday and Sunday";break;
        default:        out << "Invalid Use_day";
    }
    return out;
}





//2nd way
Use& operator++(Use& use_day) 
{
    switch (use_day) 
    {    
        case monday:    return use_day = tuesday;
        case tuesday:   return use_day = wednesday;
        case wednesday: return use_day = thursday;
        case thursday:  return use_day = friday;
        case friday:    return use_day = saturday;
        case saturday:  return use_day = sunday;
        case sunday:    return use_day = monday;
        default:        return use_day; 
               
    }
}

// 4(A.1). Function to input use_day of use
void input_use( string c, Use& use) 
{
    cout<<c;
    char choice;
    cin >> choice;
    switch (choice) 
    {
        case '0': use =  monday;    break;
        case '1': use =  tuesday;   break;
        case '2': use =  wednesday; break;
        case '3': use =  thursday;  break;
        case '4': use =  friday;    break;
        case '5': use =  saturday;  break;
        case '6': use =  sunday;    break;
        case 'd': use =  daily;     break;
        case 'm': use =  mo_fr;     break;
        case 'o': use =  once;      break;
        case 's': use =  sa_su;     break;    
        default:
          cout << "Invalid choice." << endl;
          break;
    }
}

// 6. (A3.1) Define a structure called year
struct Year 
{
    int yearValue;                   
    Use firstDayOfWeek;             
    string unit;                      
    float values[days_in_year][interval_quater_hour];
};

// 7. (A3.1) Inline function to set all quarter-hour interval values to 0.0 and return the reference variable
inline Year& zeros(Year& year) 
{
    for (int i = 0; i < days_in_year; i++) 
    {
        for (int j = 0; j < interval_quater_hour; j++) 
        {
            year.values[i][j] = 0.0;
        }
    }
    return year;
}

// 8. (A3.1) Inline function to calculate the minute of the day
inline int time(int h, int m) 
{
    return h * 60 + m;
}


// 9. (A3.1) output operator 
ostream& operator<<(ostream& out, Year& year )
{
    Use current_day = year.firstDayOfWeek;

    out<<"year"<<": "<<year.yearValue<<endl;
    for(int i=0; i<days_in_year; i++)
     {
        int q_h=0;
        out<<"Day "<<i<<": "<<current_day<<endl;
        for(int j=0; j<interval_quater_hour/4; j++)
        {
            out << setw(2) << j << ":00"<<"\t";
            for(int k=0; k<4; k++)
            {
                out <<setw(7)<< fixed << setprecision(2) << year.values[i][q_h++] << right << "\t";
            }
             out <<endl;
        }        
        out<<endl;
        ++current_day;
     }
 
   return out;
}

// 10. (A3.1) unary operator+
Year& operator+(Year& year1,  Year& year2)
{
    if (year1.yearValue != year2.yearValue && year1.firstDayOfWeek != year2.firstDayOfWeek || year1.unit != year2.unit) 
        {
            cout<<"Operands mismatch"<<endl;
        }

    if(year2.yearValue ==year1.yearValue && year2.firstDayOfWeek == year1.firstDayOfWeek &&year2.unit == year1.unit )

    {
          for (int i = 0; i < days_in_year; i++) 
          {
               for (int j = 0; j < interval_quater_hour; j++) 
                    {
                         year1.values[i][j] = (year1.values[i][j] + year2.values[i][j]);
                    }
          }
    }

    return year1;

}

// 11. (A3.1) add_consumption Funtion
void add_consumption(Year& year, int day, int start_time, int end_time, float watt)
{
    int q_min_is=15;
    int start_interval = start_time / q_min_is;
    int end_interval = end_time / q_min_is;
    int start_reminder = (q_min_is-(start_time-(start_interval * q_min_is)));
    year.values[day][start_interval] += start_reminder * watt / 60;

    for (int interval_quater_hour = start_interval + 1; interval_quater_hour < end_interval; interval_quater_hour++) 
    {
        year.values[day][interval_quater_hour] += q_min_is* watt / 60;
    }

    int end_reminder = (end_time-(end_interval * q_min_is));
    year.values[day][end_interval] += end_reminder * watt / 60;
}

// 12. (A3.1) add_consumption overloded function
void add_consumption(Year& year, Use use_day, int start_time, int end_time, float watt) 
{
    Use day= year.firstDayOfWeek; 
          int q_min_is=15;
          int start_interval = start_time / q_min_is;
          int end_interval = end_time / q_min_is;
          int start_reminder = (q_min_is-(start_time-(start_interval * q_min_is)));
          for (int i = 0; i < days_in_year; i++) 
    { 
            if ( day == use_day|| 
               (use_day == mo_fr && day >= monday && day <= friday) ||
               (use_day == sa_su && (day == saturday || day == sunday)) ||
               use_day == daily)

               {    
                  year.values[i][start_interval] += start_reminder * watt / 60;
                    for (int interval_quater_hour = start_interval + 1; interval_quater_hour < end_interval; interval_quater_hour++) 
                        {        
                            year.values[i][interval_quater_hour] += q_min_is * watt / 60;   
                        }

                        int end_reminder = (end_time-(end_interval * q_min_is));
                        year.values[i][end_interval] += end_reminder * watt / 60;
               }
          
          ++day;
     }  
          
}

// 13. (A3.1) inline sum function
inline float sum(const Year& year) 
{
    float total = 0.0;
        for (int i = 0; i < days_in_year; i++) 
            {
                for (int j = 0; j <interval_quater_hour; j++) 
                    {
                        total += year.values[i][j];
                    }
            }
    return total;
}

// 14. Main Function
int main() 
{
    cout<<"YEARLY CONSUMPTION QUARTER HOUR\n";
    Year actual, total;
    Use use;
    actual.yearValue = 2024;
    total.yearValue = 2024;
    actual.firstDayOfWeek = monday;
    total.firstDayOfWeek = monday;
    actual.unit = "watt";
    total.unit = "watt";

    zeros(actual);
    zeros(total);
    
    float price_per_kWh = 0.30;
    char choice;
  do
    {
        cout<<"q quit\n"
            <<"a add actual to total (using operator +)\n"
            <<"c annual consumption and cost (price for one kWh: 30.00 ct/kWh; calling function sum)\n"
            <<"o output actual (using operator <<)\n"
            <<"t output total (using operator <<)\n"
            <<"u add consumption according to use_day of use (call functions add_consumption)\n"
            <<"z set actual to zeros (call function zeros)\n>>";
            cin>>choice;
        switch (choice)
        {
            case 'q':exit(0);                   break;
            case 'a': total = (total + actual); break;   
            case 'o': cout << actual;           break;       
            case 't': cout << total;            break;
            case 'u':
                int start_time, end_time, h ,m, day;
                char c;
                float watt;
                Use use;

                input_use("how often it will be used?\nMonday    (0)\nTuesday   (1)\nWednesday (2)\nThursday  (3)\nFriday    (4)\nSaturday  (5)\nSunday    (6)\ndaily     (d)\nmo_fr     (m)\nonce      (o)\nsa_su     (s)?\n", use ); 
                
                if(use == once)
                {
                    cout<<"on which day? ";
                    cin>>day;
                    cout<<"from hour:minute? ";
                    cin>>setw(2)>>h>>c>>setw(2)>>m;
                    start_time = time(h,  m);
                    cout<<"to hour:minute? ";
                    cin>>setw(2)>>h>>c>>setw(2)>>m;
                    end_time = time( h,  m);
                    cout<<"how many watt it will have? ";
                    cin>>watt;
                    add_consumption(actual,  day,  start_time, end_time,  watt);
                }
                else
                {
                    cout<<"from hour:minute? ";
                    cin>>setw(2)>>h>>c>>setw(2)>>m;
                    start_time = time(h,  m);
                    cout<<"to hour:minute? ";
                    cin>>setw(2)>>h>>c>>setw(2)>>m;
                    end_time = time( h,  m);
                    cout<<"how many watt it will have? ";
                    cin>>watt;
                    add_consumption(actual,  use,  start_time, end_time,  watt);
                }

                break;  
            case 'z': actual=zeros(actual); break;  

            case 'c':
                float total_actual_price=(sum(actual)/1000)*price_per_kWh;
                float total_price=(sum(total)/1000)*price_per_kWh;
                cout<<"sum actual = "<< sum(actual) <<" Watt  (costs: " <<total_actual_price<<" EUR)"<<endl;
                cout<<"sum total = "<< sum(total)<<" Watt  (costs: " <<(sum(total)/1000)*price_per_kWh<<" EUR)"<<endl;
                break;             
           
        }
           
    } 
  while (choice != 'q'); 
  return 0;
}