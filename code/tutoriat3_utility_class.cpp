# include <iostream>
# include <math.h>
using namespace std;

// One can make a class only with static methods
// It is called a 'utility class' and it's not designed
// for instantiating objects, but to incapsulate methods

// NOTE: -if you dont write any constructor, you're blessed by the compiler with default
//       constructors, but if you make even one, you lose all the other defaults
//       - you can also 'delete' them so no one can use it, or call the 'default'
//       e.g: Mate() = default

class Mate{
    private:
        Mate() = delete;        // Delete the constructor so you can't instantiate 
    public:

    static long ridicaLaPatrat(long nr){
        return nr * nr;
    }

    static double radical(long nr){
        return sqrt(nr);
    }
};


int main(){
    cout << Mate::ridicaLaPatrat(7) << endl;
    cout << Mate::radical(49) << endl;
}