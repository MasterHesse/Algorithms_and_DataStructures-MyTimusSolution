#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Creat a struct for Dirs by Tree
struct dir
{
    map<string , dir*> subs;
}dirs[50001];
// Global counter
// (A pointer direct to the depth of each dir)
int pointer = 1;

dir* addDir(dir* dir, string dirName)
{
    //Add a child for a dir
    auto& d = dir->subs[dirName];
    // If the dir is empty then move to the next
    if (!d)
    {
        d = &dirs[pointer++];
    }
    return d;
}

// function to print the result
void printDir(dir* dir, int depth = 0)
{
    for (auto s :dir->subs)
    {
        for (int i = 0; i < depth; i++)
        {
            cout << " ";
        }
        cout << s.first << "\n";
        printDir(s.second, depth+1);
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string str, dirstr;
        cin >> str;
        stringstream ss(str);
        dir* dir = &dirs[0];
        while (getline(ss, dirstr, '\\'))
        {
            dir = addDir(dir, dirstr);
        }
    }
        stringstream out;
        printDir(&dirs[0]);
}