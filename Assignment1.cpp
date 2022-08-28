#include<bits/stdc++.h>

using namespace std;

int SDS_player(vector<int> &snum, vector<vector<int>> &u, int x)
{
    int num = -1, ind=0, x1, x2;                 //x1, x2 store the retrieved strategies with max utility
    vector <int> ui(snum[x]);                    //Utilities for player x
    vector <int> visited(u.size(), 0);

    int start = 0, prev = 0, flag = 1, curr = 0, delta=1;

    // start stores the row of the utility matrix being compared
    // prev and curr - best utility of player x from different row comparisons (for a fixed set
    // of strategies of other players, what is the max utility player i can get)

    for(int i=0; i<x; i++)
        delta *= snum[i];

    while(ind < u.size()-1)
    {
        int x1, x2;
        if(visited[start] == 1)
        {
            start++;
            continue;
        }
        visited[start] = 1;
        if(start == 0)
            prev = start;
        else
            curr = start;

        if(start == 0)
            for(int i=1; i<snum[x]; i++)
            {
                ind = start + delta;
                visited[ind] = 1;

                if(u[ind][x] == prev)
                    flag = 0;
                else if(u[ind][x] > u[prev][x])
                {
                    flag = 1;
                    prev = ind;
                }
            }
        else
            for(int i=1; i<snum[x]; i++)
            {
                ind = start + delta;
                visited[ind] = 1;

                if(u[ind][x] == curr)
                    flag = 0;
                else if(u[ind][x] > u[curr][x])
                {
                    flag = 1;
                    curr = ind;
                }
            }

        if(flag == 0)
            return -1;

        if(start == 0)
            x1 = (prev%(delta*snum[x]))/delta;
        else
            x2 = (curr%(delta*snum[x]))/delta;

        if(start != 0 && x1 != x2)
            return -1;
    }

    return x1;
}

void SDS(vector<string> &names, vector<vector<string>> &strats, vector<int> &snum, vector<vector<int>> &u, int n)
{
    for(int i=0; i<n; i++)
    {
        int a = SDS_player(snum, u, i);
        if(a == -1)
            cout<<"Strongly Dominant strategy doesn't exist for "<<names[i]<<"\n";
        else
            cout<<"Strongly Dominant strategy for "<<names[i]<<" is: "<<strats[i][a]<<"\n";
    }
}

int main()
{
    int n = 0;
    vector<string> names;               //Names of players
    vector<vector<string>> strats;      //Names of strategies
    vector<int> snum;                   //Number of strategies for each player
    vector<vector<int>> u;              //Utilities for each strategy set

    string myText;
    int part = 1;

    ifstream MyReadFile("Trial3_3player_2strat.nfg");   //Input .nfg file name here

    while (getline(MyReadFile, myText))
    {
        int a = myText.find("{");
        int b = myText.find("}");

        if(a==-1 && b!=-1)
        {
            part++;
            continue;
        }

        if(part == 1 && a != -1 && b!= -1)
        {
            int ind1, ind2;                 // To store indices of consecutive ""
            string nm;
            part ++;
            n++;
            ind1 = myText.find("\"",a + 1);
            ind2 = myText.find("\"",ind1+1);

            while(1)
            {
                nm = myText.substr(ind1+1, ind2-ind1-1);
                names.push_back(nm);

                ind1 = myText.find("\"",ind2+1);
                if(ind1 == -1)
                    break;
                ind2 = myText.find("\"",ind1+1);
                n++;
            }
        }
        else if(part == 2 && a!=-1 && b!=-1)
        {
            int ind1, ind2, k=0;
            string nm;
            ind1 = myText.find("\"",a + 1);
            ind2 = myText.find("\"",ind1+1);
            vector <string> stemp;          // Strategy names in a row (temporarily)

            while(1)
            {
                k++;
                nm = myText.substr(ind1+1, ind2-ind1-1);
                stemp.push_back(nm);

                ind1 = myText.find("\"",ind2+1);
                if(ind1 == -1)
                    break;
                ind2 = myText.find("\"",ind1+1);
            }

            strats.push_back(stemp);
            snum.push_back(k);
        }
        else if(part == 3 && a!=-1 && b!=-1)
        {
            int ind1, ind2, k=0;            // k is for integer utility value
            string nm;
            ind1 = myText.find("\"",a + 1);
            ind2 = myText.find(",",a + 1);
            vector <int> utemp;          // Utility values in a row (temporarily)

            while(1)
            {
                nm = myText.substr(ind1+2, ind2-ind1-1);
                k = stoi(nm);
                utemp.push_back(k);

                ind1 = ind2;
                if(ind2 == b)
                    break;
                ind2 = myText.find(",",ind1+1);
                if(ind2 == -1)
                    ind2 = b;
            }

            u.push_back(utemp);
        }
    }

    for(int i=0; i<n; i++)
        cout<<names[i]<<"\n";

    cout<<"\n";
    for(int i=0; i<strats.size(); i++)
    {
        for(int j=0; j<strats[i].size(); j++)
            cout<<strats[i][j]<<", ";
        cout<<"\n";
    }

    cout<<"\n";
    for(int i=0; i<u.size(); i++)
    {
        for(int j=0; j<u[i].size(); j++)
            cout<<u[i][j]<<", ";
        cout<<"\n";
    }
    cout<<"\n";

    MyReadFile.close();

    //Calling
    SDS(names, strats, snum, u, n);

    }
