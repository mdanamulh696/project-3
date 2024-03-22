
#include<iostream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;
//5
const int DAYS_IN_YEAR = 10;
const int QUARTER_HOURS_IN_DAY = 12;

const int HOURS = 2;
//1
enum Use { monday, tuesday, wednesday, thursday, friday, saturday, sunday, once, daily, mo_fr, sa_su};
//6
struct Year {
    int yearValue;
    Use firstDayOfWeek;
    string unit;
    float powerConsumption[DAYS_IN_YEAR][QUARTER_HOURS_IN_DAY];
};

//2
ostream& operator<<(ostream& os, const Use& use) {
    switch (use) {
        case once:
            os << "once";
            break;
        case daily:
            os << "daily";
            break;
        case mo_fr:
            os << "Monday to Friday";
            break;
        case sa_su:
            os << "Saturday and Sunday";
            break;
        case monday:
            os << "Monday";
            break;
        case tuesday:
            os << "Tuesday";
            break;
        case wednesday:
            os << "Wednesday";
            break;
        case thursday:
            os << "Thursday";
            break;
        case friday:
            os << "Friday";
            break;
        case saturday:
            os << "Saturday";
            break;
        case sunday:
            os << "Sunday";
            break;
    }
    return os;
}
//3
Use operator++(Use& use, int) {
    Use original = use;

    switch (use) {
        case monday:
            use = tuesday;
            break;
        case tuesday:
            use = wednesday;
            break;
        case wednesday:
            use = thursday;
            break;
        case thursday:
            use = friday;
            break;
        case friday:
            use = saturday;
            break;
        case saturday:
            use = sunday;
            break;
        case sunday:
            use = monday;
            break;
        default:
            break;
    }

    return original;
}

//4
void input_use(string prompt, Use& use) {
    char choice;
    cout << prompt;
    cin >> choice;

    switch (choice) {
        case 'o':
            use = once;
            break;
        case 'd':
            use = daily;
            break;
        case 'm':
            use = mo_fr;
            break;
        case 's':
            use = sa_su;
            break;
        case '0':
            use = monday;
            break;
        case '1':
            use = tuesday;
            break;
        case '2':
            use = wednesday;
            break;
        case '3':
            use = thursday;
            break;
        case '4':
            use = friday;
            break;
        case '5':
            use = saturday;
            break;
        case '6':
            use = sunday;
            break;
        default:
            cout << "Sorry, wrong choice" << endl;
            input_use(prompt, use);
    }
}
//7
inline Year& zeros(Year& year) {
    for (int i = 0; i < DAYS_IN_YEAR; ++i) {
        for (int j = 0; j < QUARTER_HOURS_IN_DAY; ++j) {
            year.powerConsumption[i][j] = 0.0;
        }
    }
    return year;
}

// PT2 Inline function to set all quarter-hour interval values to 1.0
inline Year& ones(Year& year) {
    for (int i = 0; i < DAYS_IN_YEAR; ++i) {
        for (int j = 0; j < QUARTER_HOURS_IN_DAY; ++j) {
            year.powerConsumption[i][j] = 1.0;
        }
    }
    return year;
}

//8
inline int time(int h, int m) {
    return h * 60 + m;
}
//9 PT1
ostream& operator<<(ostream& os, const Year& year) {
    os << "year: " << year.yearValue
       << " unit: (" << year.unit << ")\n";

    Use currentDayOfWeek = year.firstDayOfWeek;

    // Output day numbers, day of the week, and quarter-hour values
    for (int day = 0; day < DAYS_IN_YEAR; ++day) {
        os << "day " << day << ": " << currentDayOfWeek << endl;

        for (int hour = 0; hour <= HOURS; ++hour) {
            os << " " << hour << ":00" <<"\t";
            for (int quarterHour = 0; quarterHour < 4; ++quarterHour) {
                os << fixed << setprecision(2) << year.powerConsumption[day][hour * 4 + quarterHour] << "\t";
            }
            os << endl;
        }

        currentDayOfWeek++;
    }

    return os;
}
//PT3
Year operator-(const Year& year1, const Year& year2) {
    // Check if the years, first days of the week, and units match
    if (year1.yearValue != year2.yearValue ||
        year1.firstDayOfWeek != year2.firstDayOfWeek ||
        year1.unit != year2.unit) {
        cout << "Error: Years do not match for subtraction." << endl;
        return Year();
    }

    // Create a new Year structure to store the result
    Year resultYear;
    resultYear.yearValue = year1.yearValue;
    resultYear.firstDayOfWeek = year1.firstDayOfWeek;
    resultYear.unit = year1.unit;

    // Subtract quarter-hour values element by element
    for (int day = 0; day < DAYS_IN_YEAR; ++day) {
        for (int quarterHour = 0; quarterHour < QUARTER_HOURS_IN_DAY; ++quarterHour) {
            resultYear.powerConsumption[day][quarterHour] =
                year1.powerConsumption[day][quarterHour] - year2.powerConsumption[day][quarterHour];
        }
    }

    return resultYear;
}
//PT4
Year operator*(float multiplier, const Year& year) {
    // Create a new Year structure to store the result
    Year resultYear;
    resultYear.yearValue = year.yearValue;
    resultYear.firstDayOfWeek = year.firstDayOfWeek;
    resultYear.unit = year.unit;

    // Multiply quarter-hour values element by element with the floating point number
    for (int day = 0; day < DAYS_IN_YEAR; ++day) {
        for (int quarterHour = 0; quarterHour < QUARTER_HOURS_IN_DAY; ++quarterHour) {
            resultYear.powerConsumption[day][quarterHour] =
                multiplier * year.powerConsumption[day][quarterHour];
        }
    }

    return resultYear;
}
//PT5
void set_unit(Year& year, const char* newUnit) {
    // Set the component unit of the structure variable to the value of the character string
    year.unit = newUnit;
}

//10
Year operator+(const Year& year1, const Year& year2) {
    // Check if the years, first days of the week, and units match
    if (year1.yearValue != year2.yearValue ||
        year1.firstDayOfWeek != year2.firstDayOfWeek ||
        year1.unit != year2.unit) {
        cout << "Error: Years do not match for addition." << endl;
        return Year();
    }

    // Create a new Year structure to store the result
    Year resultYear;
    resultYear.yearValue = year1.yearValue;
    resultYear.firstDayOfWeek = year1.firstDayOfWeek;
    resultYear.unit = year1.unit;

    // Add quarter-hour values element by element
    for (int day = 0; day < DAYS_IN_YEAR; ++day) {
        for (int quarterHour = 0; quarterHour < QUARTER_HOURS_IN_DAY; ++quarterHour) {
            resultYear.powerConsumption[day][quarterHour] =
                year1.powerConsumption[day][quarterHour] + year2.powerConsumption[day][quarterHour];
        }
    }

    return resultYear;
}

//11
void add_consumption(Year& year, int day, int startMinute, int endMinute, float wattage) {
    int startQuarterHour = startMinute / 15;
    int endQuarterHour = endMinute / 15;
    float wattagePerMinute = wattage / 60;
    int startTimeMinute = startMinute % 60;
    int endTimeMinute = endMinute % 60;
    // Update the power consumption array
    for (int quarterHour = startQuarterHour; quarterHour <= endQuarterHour; ++quarterHour) {
        if (quarterHour == startQuarterHour){
            if (quarterHour == endQuarterHour ){
                year.powerConsumption[day][quarterHour] += (endTimeMinute - startTimeMinute) * wattagePerMinute;
            } else {
                year.powerConsumption[day][quarterHour] += ((((quarterHour % 4) + 1) * 15) - startTimeMinute) * wattagePerMinute;
            }
        }
        else if (quarterHour == endQuarterHour ){
            year.powerConsumption[day][quarterHour] += (endTimeMinute - ((quarterHour % 4) * 15)) * wattagePerMinute;
        }
        else {
            year.powerConsumption[day][quarterHour] += 15 * wattagePerMinute;
        }
    }
}

//12
void add_consumption(Year& year, Use use, int startMinute, int endMinute, float wattage) {
    int dayOfWeek;

    switch (use) 
    {
        case monday:
        case tuesday:
        case wednesday:
        case thursday:
        case friday:
        case saturday:
        case sunday:
            for (int i = 0; i < DAYS_IN_YEAR; ++i) {
                dayOfWeek = i % 7;
                if (dayOfWeek == use) 
                {
                    add_consumption(year, i, startMinute, endMinute, wattage);
                }
            }
            break;

        case daily:
            for (int i = 0; i < DAYS_IN_YEAR; ++i) {
                add_consumption(year, i, startMinute, endMinute, wattage);
            }
            break;
        case mo_fr:
            for (int i = 0; i < DAYS_IN_YEAR; ++i) {
                dayOfWeek = i % 7;
                if (dayOfWeek == monday || dayOfWeek == tuesday ||
                    dayOfWeek == wednesday || dayOfWeek == thursday ||
                    dayOfWeek == friday) {
                    add_consumption(year, i, startMinute, endMinute, wattage);
                }
            }
            break;
        case sa_su:
            for (int i = 0; i < DAYS_IN_YEAR; ++i) {
                dayOfWeek = i % 7;
                if (dayOfWeek == saturday || dayOfWeek == sunday) {
                    add_consumption(year, i, startMinute, endMinute, wattage);
                }
            }
            break;
    }

}

//13
inline float sum(const Year& year) {
    float totalSum = 0.0;

    for (int day = 0; day < DAYS_IN_YEAR; ++day) {
        for (int quarterHour = 0; quarterHour < QUARTER_HOURS_IN_DAY; ++quarterHour) {
            totalSum += year.powerConsumption[day][quarterHour];
        }
    }

    return totalSum;
}


int main() {
    const int TEST_DAYS_IN_YEAR = 10;
    const int TEST_QUARTER_HOURS_IN_DAY = 12;
    float value;  // Variable to store scalar for scalar multiplication
    char newUnit[50];  // Array to store the new unit string
    Year actual, total;

    // Initialize actual and total structures
    actual.yearValue = total.yearValue = 2024;
    actual.firstDayOfWeek = total.firstDayOfWeek = monday;
    actual.unit = total.unit = "Watt";

    // Initialize powerConsumption arrays to zeros for initial tests
    actual = zeros(actual);
    total = zeros(total);

    float pricePerkWh = 0.30;

    cout << "YEARLY CONSUMPTION QUARTER HOUR" << endl;
    char choice;
    do {
        cout << "q quit" << endl;
        cout << "a add actual to total (using operator +)" << endl;
        cout << "m subtract actual from total (using operator -)" << endl;
        cout << "s scalar multiplication" << endl;
        cout << "c change unit" << endl;
        cout << "v sum up values" << endl;
        cout << "o output actual (using operator <<)" << endl;
        cout << "t output total (using operator <<)" << endl;
        cout << "u add consumption according to frequency of use (call functions add_consumption)" << endl;
        cout << "y set actual to ones (call function ones)" << endl;
        cout << "z set actual to zeros (call function zeros)" << endl;

        cin >> choice;

        switch (choice) {
            case 'a':
                total = total + actual;
                break;
            case 'v':
                cout << "sum actual = " << fixed << setprecision(2) << sum(actual) << " " << actual.unit <<")" << endl;
                cout << "sum total = " << fixed << setprecision(2) << sum(total) << " " << total.unit <<")" << endl;
                break;
            case 'o':
                cout << actual;
                break;
            case 't':
                cout << total;
                break;
            case 'u':
                Use use;
                input_use("how often it will be used?\nMonday (0)\nTuesday (1)\nWednesday (2)\nThursday  (3)\nFriday    (4)\nSaturday  (5)\nSunday    (6)\ndaily     (d)\nmo_fr     (m)\nonce      (o)\nsa_su     (s)?\n", use);
                int day;
                if (use == once){
                    cout << "on which day? ";
                    cin >> day;
                }
                int fromHour, fromMinute, toHour, toMinute;
                float wattage;
                char colon;
                cout << "from hour:minute? ";
                cin >> fromHour >> colon >> fromMinute;
                cout << "to hour:minute? ";
                cin >> toHour >> colon >> toMinute;
                cout << "how many watt it will have? ";
                cin >> wattage;
                if (use == once){
                    add_consumption(actual, day, time(fromHour, fromMinute), time(toHour, toMinute), wattage);
                } else{
                    add_consumption(actual, use, time(fromHour, fromMinute), time(toHour, toMinute), wattage);
                }
                break;
            case 'z':
                actual = zeros(actual);
                break;
            case 'm':
                // Subtract actual from total
                total = total - actual;
                break;

            case 's':
                // Scalar multiplication
                char choice;
                cout << "a for actual\nt for total\n";
                cin >> choice;
                cout << "value of scalar? ";
                cin >> value;
                if (choice == 'a') {
                    actual = value * actual;
                } else if (choice == 't') {
                    total = value * total;
                }
                break;

            case 'c':
                // Change unit
                char uChoice;
                cout << "a for actual\nt for total\n";
                cin >> uChoice;
                cout << "what is the new unit? ";
                cin.ignore();  // Ignore any newline character left in the buffer
                cin.getline(newUnit, sizeof(newUnit));
                if (uChoice == 'a') {
                    set_unit(actual, newUnit);
                } else if (uChoice == 't') {
                    set_unit(total, newUnit);
                }
                break;

            case 'y':
                ones(actual);
                break;
            case 'q':
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 'q');

    return 0;
}

