#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
string tohumanlang (string str)
{
    string temp;
    for(long long i=0; i<str.length(); i++)
        temp+='-';
    if(temp==str)
        return "1";
    char ch;
    long long counter=0;
    temp.clear();
    for(long long i=str.length()-1; i>=0; i--)
    {
        if(str[i]=='1')
        {
            ch=65+counter;
            temp+=ch;
        }
        if(str[i]=='0')
        {
            ch=65+counter;
            temp+=ch;
            temp+='\'';
        }
        counter++;
    }
    return temp;
}
void input (vector <long long> &vect, long long *counter,int flag,vector <long long> decmins,long long n)
{
    long long temp;
    while(1)
    {
        while (!(std::cin >> temp)||(temp<0&&temp!=-1))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter an *integer*: ";
        }
        if(temp==-1)
            break;
        if(find(decmins.begin(),decmins.end(),temp)!=decmins.end())
        {
            cout << "Invalid Don't care as it belongs to Minterms";
            continue;
        }
        vect.push_back(temp);
        (*counter)++;

    }
    sort(vect.begin(),vect.end());
}
void tobinstr (vector <long long> &invect, vector < pair < pair <int,int>,pair < vector <long long>,string> > > &ovect, long long n)
{
    vector <long long> tempo;
    long long temp,ones=0;
    string str;
    for (long long i=0; i<(int)invect.size(); i++)
    {
        temp=invect[i];
        while(temp!=0)
        {
            if(temp&1u)
            {
                ones++;
                str+='1';
            }
            else
                str+='0';
            temp>>=1;
        }
        while((int)str.size()<n)
            str+='0';
        tempo.push_back(invect[i]);
        ovect.push_back(make_pair(make_pair(0,ones),make_pair(tempo,str)));
        tempo.clear();
        str.clear();
        ones=0;
    }
}
void getprimes (map <string,long long > &deprimeconv,map < long long,string> &primeconv,vector < pair < pair <int,int>,pair < vector <long long>,string> > > &invect, set < pair < vector <long long>,string> > &oset, long long startercount, long long n )
{
    vector <long long> tempo;
    long long temp=0,prevcount=0,diff=0,posi=0;
    string str;
    while(startercount!=prevcount)
    {
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
        for (long long o=prevcount; o<invect.size(); o++)
        {
            string tempot=invect[o].second.second;
            reverse(tempot.begin(),tempot.end());
            cout <<"\n  "<<tempot<<"\tcovers\t  (";
            for (long long p=0; p<invect[o].second.first.size(); p++)
                cout <<invect[o].second.first[p]<<",";
            printf("\b");
            cout <<")";
        }

        prevcount=startercount;

        for (long long i=temp; i<prevcount; i++)
        {
            for (long long j=temp; j<prevcount; j++)
            {
                if(invect[j].first.second-invect[i].first.second==1)
                {
                    diff=0;
                    for(long long k=0; k<n; k++)
                        if(invect[j].second.second[k]!=invect[i].second.second[k])
                        {
                            diff++;
                            posi=k;
                        }
                    if(diff==1)
                    {
                        str=invect[j].second.second;
                        str[posi]='-';
                        invect[i].first.first=1;
                        invect[j].first.first=1;
                        invect.push_back(make_pair(make_pair(0,invect[i].first.second),make_pair(tempo,str)));
                        for(long long q=0; q<(int)invect[i].second.first.size(); q++)
                            invect.back().second.first.push_back(invect[i].second.first[q]);
                        for(long long q=0; q<(int)invect[j].second.first.size(); q++)
                            invect.back().second.first.push_back(invect[j].second.first[q]);

                        startercount++;
                    }
                }
            }
        }

        temp=prevcount;
    }
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    for (long long i=0; i<(int)invect.size(); i++)
    {
        if(invect[i].first.first==0)
        {
            sort(invect[i].second.first.begin(),invect[i].second.first.end());
            oset.insert(make_pair(invect[i].second.first,invect[i].second.second));

        }
    }
    long long i=0;
    for (set < pair < vector <long long>,string> >::iterator j=oset.begin(); j!=oset.end(); j++,i++)
        primeconv[i]=(*j).second;
    for (i=0; i<(int)primeconv.size(); i++)
        deprimeconv[primeconv[i]]=i;
}

void outputprimes (set < pair < vector <long long>,string> > &inset,long long n)
{
    cout << "\n\n  Prime Implicants : \n\n";
    string str;
    for(long long k=0; k<n; k++)
        str+='-';
    for (set < pair < vector <long long>,string> >::iterator i=inset.begin(); i!=inset.end(); i++)
    {
        cout <<"  "<< tohumanlang((*i).second) << "\tcovers\t(";
        for (long long k=0; k<(int)(*i).first.size(); k++)
            cout << (*i).first[k] <<',';
        printf("\b)\n");
    }
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
}

void geteprimes (vector <long long> &dontcares,vector <long long> &decmins,vector < pair < long long, vector <string> > > &mincover,map <long long,int> &minterms,set < pair < vector <long long>,string> > &primes,set < pair < string, vector <long long> > > &eprimes)
{
    vector <string> tempo;
    for (long long i=0; i<decmins.size(); i++)
    {
        minterms[decmins[i]]=i;
        mincover.push_back(make_pair(decmins[i],tempo));
    }
    for (set < pair < vector <long long>,string> >::iterator i=primes.begin(); i!=primes.end(); i++)
    {
        for (long long j=0; j<(*i).first.size(); j++)
        {
            if(find(dontcares.begin(),dontcares.end(),(*i).first[j])!=dontcares.end())
                continue;
            mincover[minterms[(*i).first[j]]].second.push_back((*i).second);
        }
    }
    for (long long i=0; i<mincover.size(); i++)
    {
        if(mincover[i].second.size()==1)
        {
            set < pair < vector <long long>,string> >::iterator j=primes.begin();
            while((*j).second.compare(mincover[i].second[0])!=0)
                j++;
            eprimes.insert(make_pair(mincover[i].second[0],(*j).first));
        }
    }
}

void outputeprimes(vector <long long> dontcares,set < pair < string, vector <long long> > > &eprimes,long long n)
{
    string str;
    cout << "\n\n  Essential Prime Implicants:\n\n";
    str.clear();
    for(long long k=0; k<n; k++)
        str+='-';
    for (set < pair < string, vector <long long> > >::iterator i=eprimes.begin(); i!=eprimes.end(); i++)
    {
        cout <<"  "<<tohumanlang((*i).first) << "\tcovers\t(";
        for (long long k=0; k<(int)(*i).second.size(); k++)
            cout << (*i).second[k]<<',';
        printf("\b)\n");
    }
    printf("\n");
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
}

void takeeprimes (map <string,long long > &deprimeconv,vector < pair < long long, vector <string> > > &mincover,vector < vector <long long> > &intiate,set < pair < string, vector <long long> > > &eprimes,vector <string> &expression,set <long long> &coveredmin,vector <long long> &dontcares)
{
    vector <long long>temp;
    for ( set < pair < string, vector <long long> > >::iterator i=eprimes.begin(); i!=eprimes.end(); i++)
    {
        for(long long j=0; j<(*i).second.size(); j++)
        {
            if(find(dontcares.begin(),dontcares.end(),(*i).second[j])!=dontcares.end())
                continue;
            coveredmin.insert((*i).second[j]);
        }
        expression.push_back((*i).first);
    }
    for(long long i=0; i<mincover.size(); i++)
    {
        if(coveredmin.find(mincover[i].first)==coveredmin.end())
        {
            for(long long j=0; j<mincover[i].second.size(); j++)
                temp.push_back(deprimeconv[mincover[i].second[j]]);
            intiate.push_back(temp);
            temp.clear();
        }

    }

}

long long cost (vector<string> &exp)
{
    long long cost=0,invert=0;
    char inverter[exp[0].length()]= {0};
    for (long long i=0; i<exp.size(); i++)
    {
        for(long long j=0; j<exp[i].length(); j++)
        {
            if(exp[i][j]=='0')
            {
                inverter[j]=1;
                cost++;
            }
            else if(exp[i][j]=='1')
                cost++;
        }
    }
    for (long long i=0; i<exp[0].length(); i++)
        invert+=inverter[i];
    cost+=invert;
    if(exp.size()!=1)
        cost+=exp.size();

    if(cost==1)
        return 0;
    if(cost==2&&invert==1)
        return 1;
    return cost;
}
void petrick (set < set<long long> > &petexp,vector < vector <long long> > &intiate,vector < vector <long long > > &mini)
{

    set <long long > temp;
    set <set <long long > > tempo;
    long long popsize;
    for(long long i=0; i<intiate[0].size(); i++)
    {
        temp.insert(intiate[0][i]);
        tempo.insert(temp);
        temp.clear();
    }

    for(long long i=1; i<intiate.size(); i++)
    {
        for(long long j=0; j<intiate[i].size(); j++)
        {
            for(set < set <long long > >::iterator k=tempo.begin(); k!=tempo.end(); k++)
            {
                temp=(*k);
                temp.insert(intiate[i][j]);
                petexp.insert(temp);
                temp.clear();
            }
        }
        tempo=petexp;
        petexp.clear();
    }
    mini.resize(tempo.size());
    long long k=0;
    for(set< set <long long> >::iterator i=tempo.begin(); i!=tempo.end(); i++,k++)
        for (set <long long>::iterator j=(*i).begin(); j!=(*i).end(); j++)
            mini[k].push_back(*j);
    cout <<"\n\n";
}

void finalexp (vector <long long> dontcares,map <long long,string> &primeconv,vector <long long> &decmins,set < set<long long> > &petexp,vector < vector <long long> > &intiate,vector < vector <long long > > &mini,vector <string> &expression)
{
    if(decmins.size()==0&&dontcares.size()==0)
    {
        cout << "  Minimal Form : F = 0\n\n";
        cout << "  Total cost = 0 unit cost.\n\n";
        return;
    }
    if(decmins.size()==0)
    {
        cout << "  Minimal Form : F = 1\n\n";
        cout << "  Total cost = 0 unit cost.\n\n";
        return;
    }
    if(intiate.size()!=0)
    {
        vector <pair <int,vector <string> > > comparison;
        vector <string> temp;
        petrick(petexp,intiate,mini);
        for (long long i=0; i<mini.size(); i++)
        {
            for(long long j=0; j<mini[i].size(); j++)
                temp.push_back(primeconv[mini[i][j]]);
            comparison.push_back(make_pair(cost(temp),temp));
            temp.clear();
        }
        sort(comparison.begin(),comparison.end());
        for (long long i=0; i<comparison[0].second.size(); i++)
            expression.push_back(comparison[0].second[i]);
    }
    cout << "  Minimal Form :\n\n  F = ";
    for (long long i=0; i<expression.size(); i++)
    {
        cout << tohumanlang(expression[i]) << ' ';
        if(i!=expression.size()-1)
            cout <<'+' << ' ';
    }
    cout <<"\n\n";
    cout << "  Total cost = " << cost(expression) <<" unit cost.";
    cout <<"\n\n";
}

void stoptheuser (long long *n,vector <long long> &vect1, long long *counter1,vector <long long> &vect2, long long *counter2)
{
    cout <<"  Welcome to Quine Mccluskey solver !\n\n  Please enter number of variables : ";
    while (!(std::cin >> *n)||*n<=0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a *Positive integer*: ";
    }
    cout << "\n  Please enter Minterms separated by space & followed by -1 then press Enter key : ";
    input(vect1,counter1,0,vect1,*n);
    cout << "\n  Please enter Don't Cares separated by space & followed by -1 then press Enter key : ";
    input(vect2,counter2,1,vect1,*n);
}
int main()
{
    long long n;
    long long mincount=0,duncarecount=0,startercount=0;
    string str;
    vector <long long> decmins;
    vector <long long> dontcares;
    map <long long,int> minterms;
    map <long long,string> primeconv ;
    map <string,long long > deprimeconv ;
    vector < pair < long long, vector <string> > > mincover;
    vector  < pair < pair <int,int>,pair < vector <long long>,string> > > bin;
    set < pair < vector <long long>,string> > primes;
    set < pair < string, vector <long long> > > eprimes;
    vector <string> expression;
    set <long long> coveredmin;
    vector < vector <long long> > intiate;
    set < set<long long> > petexp;
    vector < vector <long long > > mini;
    stoptheuser(&n,decmins,&mincount,dontcares,&duncarecount);
    tobinstr(decmins,bin,n);
    tobinstr(dontcares,bin,n);
    startercount=mincount+duncarecount;
    getprimes(deprimeconv,primeconv,bin,primes,startercount,n);
    outputprimes(primes,n);
    geteprimes(dontcares,decmins,mincover,minterms,primes,eprimes);
    outputeprimes(dontcares,eprimes,n);
    takeeprimes(deprimeconv,mincover,intiate,eprimes,expression,coveredmin,dontcares);
    finalexp(dontcares,primeconv,decmins,petexp,intiate,mini,expression);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    system("pause");
    return 0;

}
