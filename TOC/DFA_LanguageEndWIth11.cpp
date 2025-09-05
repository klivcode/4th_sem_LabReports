// cpp program for DFA for the laguage od strings over {0,1}
// that end with 11

#include<iostream>
#include<string>
using namespace std;

int main(){
    string str;
    int state =0;
    cout<<"Enter the string: ";
    cin>>str;

    for(int i=0; i<str.length(); i++){
        if(str[i] !='0' && str[i]!='1')
        {
            cout<<"String not accepted .\nPlease enter a string over {0,1}"<<endl;
            return 0;
        }

        if (state == 0 && str[i] == '0')
            state = 0;
        else if (state == 0 && str[i] == '1')
            state = 1;
        else if (state == 1 && str[i] == '0')
            state = 0;
        else if (state == 1 && str[i] == '1')
            state = 2;
        else if (state == 2 && str[i] == '0')
            state = 0;
        else if (state == 2 && str[i] == '1')
            state = 2; // <-- FIX: stay in q2, not go to q1
    }
    if(state == 2)
        cout << "String accepted";
    else
        cout << "String not accepted";

    return 0;
}