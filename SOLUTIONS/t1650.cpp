#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

const int maxn = 10000, maxm = 50000, maxk = 50000;

struct City
{
    long long money;
    int days;
    string names;
} city[maxn + maxk];

struct billionaires
{
    string names;
    long long money;
    City* location;
} persons[maxn];

// To quick match person and the city and rank them,
// Map would be a good solution
unordered_map<string, billionaires*> personMap; // Match names for person
map<string, City*> cityMap; // Match names for city
set<pair<long long, City*>, greater<>> scoreBoard; // Rank the citys by money

int main()
{
    ios::sync_with_stdio(false);
    int n = 0; // The number of billionaires
    int m = 0, k = 0;//the number of days and the number of travels of the billionaires
    int c = 0; // Counter for cities
    
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name;
        string location;
        long long money;
        cin >> name >> location >> money; // read in the message

        personMap[name] = &persons[i]; // Match a person by name
    
        if (!cityMap[location]) //If the city is not exsit
            cityMap[location] = &city[c++]; // Match the new city to the City array

        persons[i].location = cityMap[location];
        persons[i].money = money; // add new record

        cityMap[location]->names = location;
        cityMap[location]->money += money;
    }
    for (auto c :cityMap)
        scoreBoard.insert ( {c.second->money, c.second}); //insert Money and city

    cin >> m >> k;
    
    int prevday = 0;
    int day;
    string name;
    string place;
    int counter = 0;
    while (true)
    {
        counter ++;
        
        // if success(read in), then return false
        bool finished = false;
        if (counter > k)
            finished = true;
        
        if (!finished)
        {
            std::cin >> day >> name >> place ;
        }
        

        if (finished)
        {
            day = m;
        }
        
        if (day != prevday)
        {
            auto it2 = scoreBoard.begin(); // The begin iter point to the first element
            auto it = it2++; // Point to the next

            if (it2 == scoreBoard.end() || it->first > it2->first)
            // If it2 has point to the end(No element now)
            // Or The element is smalller than next element
            // Update the number of days the current city has stayed on the list
                it->second->days += day - prevday;
            
        }
        
        
        if (finished) // End
        {
          break;
        }
    
        if (!cityMap[place]) // If a new city occur
        {
            // Add it into Map
            cityMap[place] = &city[c++];
            cityMap[place]->names = place;
        }
        
        // Update the set and structure City
        auto nextPlace = cityMap[place]; // Match by city's name
        auto person = personMap[name]; // Match by person's name
        auto prevPlace = person->location; // Location of a person
        auto prevMoney = prevPlace->money; //Money of a city


        scoreBoard.erase({prevMoney, prevPlace}); // Remove the info of the prev city
        prevPlace->money -= person->money; // Add a person's money to next city

        //Insert the updated original city info back into the set
        //to update its position in the rankings 
        scoreBoard.insert({prevPlace->money, prevPlace});


        scoreBoard.erase({nextPlace->money, nextPlace}); // Remove the info of next City
        nextPlace->money += person->money; //Add money to the new city
        scoreBoard.insert({nextPlace->money, nextPlace}); // Insert back


        person->location = nextPlace; // Update the location to nextcity
        prevday = day; // Update the prevday to day      

    }
    
    // Define an output (City name, The day the city contain the greatest money)
    vector<pair<string, int>>output;
    for (auto& r: scoreBoard)
        if (r.second->days) // If exist , add like (name , day)
            output.push_back(make_pair(r.second->names, r.second->days));
    
    sort(output.begin(), output.end());
    for(auto& o : output)
        cout << o.first << " " << o.second << "\n";

}
