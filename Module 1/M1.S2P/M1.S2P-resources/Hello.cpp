#include <iostream>
using namespace std;

int num_size = 4;

int sum(int n)
{
    static int result = 0;

    result += n;
    
    return result;
}

int main()
{
    int *p;
    int i = 0;

    p = new int[num_size];

    int total = 0;

    for (i = 0; i < num_size; i++)
    {
        cout << "enter number " << i + 1  << ": ";
        cin >> p[i];
        total = sum(p[i]);
    }

    delete p;

    cout<<"the final result is "<<total<<"\n";

    return 0;
}