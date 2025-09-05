// cpp program for DFA accepting the string over {a,b}
// that do not end with ab


#include<iostream>
#include<string>
using namespace std;

int main()
{
    string str;
    char state = '0';
    cout << "Enter the string: ";
    cin >> str;

     for (int i = 0; i < str.length(); i++)
    {
        
        if (str[i] != 'a' && str[i] != 'b')
        {
            cout << "String not accepted.\nPlease enter a string over {a,b}" << endl;
            return 0;
        }

      
        if (state == 0 && str[i] == 'a')
            state = 1;
        else if (state == 0 && str[i] == 'b')
            state = 0;
        else if (state == 1 && str[i] == 'a')
            state = 1;
        else if (state == 1 && str[i] == 'b')
            state = 2;
        else if (state == 2 && str[i] == 'a')
            state = 1;
        else if (state == 2 && str[i] == 'b')
            state = 0;
    }

  
    if (state == 0 || state == 1)
        cout << "String accepted";
    else
        cout << "String not accepted";

    return 0;
}