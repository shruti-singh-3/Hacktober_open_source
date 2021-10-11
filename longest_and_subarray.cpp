#include <iostream>
#include <cmath>

using namespace std;

int check_bits (int n)
{
    int b=0;
  for (; n > 0; n /= 2)
    b++;
  return b;
}
int dec(int b)
{
    int deci=0;
    for(int i=0;i<b;i++)
    deci=int(pow(2,i))+deci;
    return deci;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int less_b=check_bits(n) - 1;
        int m = n - dec(less_b);
        int l = dec(less_b) - dec(less_b - 1);
        if(m >= l)
        cout<<m<<endl;
        else
        cout<<l<<endl;
        
    }

    return 0;
}
