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

                if(u[ind][x] == u[prev][x])
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

        start++;
    }

    return x1;
}

int WDS_player(vector<int> &snum, vector<vector<int>> &u, int x)
{
    int num = -1, ind=0, fl1=0, fl2=0;               //fl1, fl2 check the strictly greater condition in WDS
    vector <int> ui(snum[x]);                    //Utilities for player x
    vector <int> visited(u.size(), 0);

    int start = 0, prev = 0, curr = 0, delta=1;

    for(int i=0; i<x; i++)
        delta *= snum[i];

    while(ind < u.size()-1)
    {
        int x1;
        if(visited[start] == 1)
        {
            start++;
            continue;
        }
        visited[start] = 1;

            prev = start;

            for(int i=1; i<snum[x]; i++)
            {
                ind = start + delta;
                visited[ind] = 1;

                if(u[ind][x] > u[prev][x])
                {
                    fl1 = 1;
                    prev = ind;
                }
                else if(u[ind][x] == u[prev][x])
                {
                    fl1 = 0;
                }
            }

        if(fl1 == 1)
            fl2 = 1;

        x1 = (prev%(delta*snum[x]))/delta;

        if(start == 0)
            curr = x1;
        else if(curr != x1)
            return -1;

        start++;
    }
    if(fl2 == -1)
        return -1;

    return curr;
}

vector<int> VWDS_player(vector<int> &snum, vector<vector<int>> &u, int x)
{
    int num = -1, ind=0, x1, x2;                 //x1, x2 store the retrieved strategies with max utility
    vector <int> ui(snum[x]);                    //Utilities for player x
    vector <int> visited(u.size(), 0);
    vector <int> v;
    vector <int> v2;

    int start = 0, prev = 0, curr = 0, delta=1;

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

            prev = start;
            v2.push_back(prev);

            for(int i=1; i<snum[x]; i++)
            {
                ind = start + delta;
                visited[ind] = 1;

                if(u[ind][x] > u[prev][x])
                {
                    prev = ind;
                    v2.clear();
                    v2.push_back(ind);
                }
                else if(u[ind][x] == u[prev][x])
                    v2.push_back(ind);
            }

        if(start != 0)
        for(int i=0; i<v2.size(); i++)
        {
            int f = 0;
            x1 = (v2[i]%(delta*snum[x]))/delta;
            for(int j=0; j<v.size(); j++)
            {
                if(x1 == v[j])
                {
                    f = 1;
                    break;
                }
            }
            if(f == 0)
            {
                v.clear();
                v.push_back(-1);
                return v;
            }
        }
        else
        for(int i=0; i<v2.size(); i++)
        {
            x1 = (v2[i]%(delta*snum[x]))/delta;
            v.push_back(v2[i]);
        }

        start++;
    }

    return v;
}


void SDS(vector<string> &names, vector<vector<string>> &strats, vector<int> &snum, vector<vector<int>> &u, int n)
{
    vector <string> store;
    int cnt=0;
    for(int i=0; i<n; i++)
    {
        int a = SDS_player(snum, u, i);
        if(a == -1)
            cout<<"Strongly Dominant strategy doesn't exist for "<<names[i]<<"\n";
        else
        {
            cout<<"Strongly Dominant strategy for "<<names[i]<<" is: "<<strats[i][a]<<"\n";
            store.push_back(strats[i][a]);
            cnt++;
        }
    }
    if(cnt == n)
    {
        cout<<"Strongly dominant strategy equilibrium exists and it is:\n";
        for(int i=0; i<n; i++)
            cout<<"Player "<<i+1<<": "<<store[i]<<"\n";
        cout<<"\n";
    }
    else
        cout<<"Strongly dominant strategy equilibrium does not exist\n\n";
}

void WDS(vector<string> &names, vector<vector<string>> &strats, vector<int> &snum, vector<vector<int>> &u, int n)
{
    vector <string> store;
    int cnt=0;
    for(int i=0; i<n; i++)
    {
        int a = WDS_player(snum, u, i);
        if(a == -1)
            cout<<"Weakly Dominant strategy doesn't exist for "<<names[i]<<"\n";
        else
        {
            cout<<"Weakly Dominant strategy for "<<names[i]<<" is: "<<strats[i][a]<<"\n";
            store.push_back(strats[i][a]);
            cnt++;
        }
    }
    if(cnt == n)
    {
        cout<<"Weakly dominant strategy equilibrium exists and it is:\n";
        for(int i=0; i<n; i++)
            cout<<names[i]<<": "<<store[i]<<"\n";
        cout<<"\n";
    }
    else
        cout<<"Weakly dominant strategy equilibrium does not exist\n\n";
}

void VWDS(vector<string> &names, vector<vector<string>> &strats, vector<int> &snum, vector<vector<int>> &u, int n)
{
    vector<vector<string>> store(n);
    vector<int> v;
    int cnt=0;
    for(int i=0; i<n; i++)
    {
        v = VWDS_player(snum, u, i);
        if(v[0] == -1)
            cout<<"Very weakly dominant strategy doesn't exist for "<<names[i]<<"\n";
        else
        {
            cout<<"Very weakly dominant strategy for "<<names[i]<<" is/are: ";
            for(int j=0; j<v.size(); j++)
            {
                cout<<strats[i][v[j]]<<", ";
                store[i].push_back(strats[i][v[j]]);
            }
            cout<<"\n";
            cnt++;
        }
    }
    if(cnt == n)
    {
        cout<<"Very weakly dominant dominant strategy equilibrium exists\n";
    }
    else
        cout<<"Very weakly dominant strategy equilibrium does not exist\n";
}

int main()
{
    int n = 0;
    vector<string> names;               //Names of players
    vector<vector<string>> strats;      //Names of strategies
    vector<int> snum;                   //Number of strategies for each player
    vector<vector<int>> u;              //Utilities for each strategy set

    string myText, str;
    int part = 1;

    cout<<"Enter filename (with .nfg extension)\n";
    cin>>str;

    ifstream MyReadFile(str);   //Input .nfg file name here

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
    WDS(names, strats, snum, u, n);

    }
