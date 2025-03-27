#include <iostream>
#include <string>

using namespace std;

class Calculator {
    private:
    static int counter_id;
    const int id = counter_id;                                               // const int id = counter_id++; Would this work?
    string procesor;                                                         // How would it affect the initialization list?
    int ram;
    bool placa_video;
    
    public:
    // TIP: Group methods by their purpose for readability

    // Constructors 
    Calculator();
    Calculator(string procesor, bool placa_video, int ram);     // NOTE: We can have as many constructors as we want
    Calculator(string procesor);                                //       thanks to FUNCTION OVERLOADING
    Calculator(const Calculator& obj);
    // Operators
    Calculator& operator=(const Calculator& obj);               // We return Class& to have a = b = c <=> a = (b = c)
    // Getters
    int getId()const{return this->id;}                          // Care for the 'const'. We can make it inline
    // Setters
    // Methods
    // Static Methods
    static void functie(){                                      // Static Methods only work with static attributes
        counter_id = 10;                                        // This one has no purpose. Made it inline for simplitude
        cout<<counter_id;
    }

    ~Calculator(){}                                             // Here we free memory manually allocated, we dont have that yet
};
 
int Calculator::counter_id = 1;                                 // Static attributes ARE ALWAYS initialized OUTSIDE the class

Calculator::Calculator():id(counter_id++){                      // 'const attributes SHOULD be initialized in the INITIALIZATION LIST
    this->procesor = "unknown";                                 // We can put all the attributes in the list
    this->placa_video = true;                                   // We list them below for readability
    this->ram = 8;                                              // 'this->' is not mandatory
    cout<<"Fara parametri\n";
}

Calculator::Calculator(string procesor):id(counter_id++){       // We can put anything that we want as a parameter, not necessarily
    this->procesor = procesor;                                  // a parameter for each attribute
    this->placa_video = false;
    this->ram = 100000;
    cout<<"Cu parametri\n";
}

Calculator::Calculator(string procesor, bool placa_video, int ram):id(counter_id++){
    this->procesor = procesor;                                  // NOTE: Here 'this->' solved the ambiguity between params and attributes
    this->placa_video = placa_video;                            // You can use 'procesor_'  or some other name to differentiate them
    this->ram = ram;                                            // We personally use this convension
    cout<<"Altu cu parametri\n";                                // BUT BE CONSISTENT, use only one convention for all Constructors !!!
}                                                               // NOTE: In python we use _function, _attribute to denote that it's private
                                                                // NOTE: Variables with the prefix '_' or '__' are reserved to the system

Calculator::Calculator(const Calculator& obj):id(counter_id++){
    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
    cout<<"Copy constructor\n";
}

Calculator& Calculator::operator=(const Calculator& obj){       // NOTE: we dont copy the id, we want them to be unique
    cout<<"Operator =\n";
    if (this == &obj)                                           // obj = obj is a waste of computation
        return *this;
    
    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
    return *this;                                               // Why '*this'? What's the type of 'this'
}

int main(){
    // What would this print and why?
    Calculator x;
    Calculator a("proc", 0, 10000);
    Calculator b = a;
    x = a;
    cout << x.getId() << " " << a.getId() << " " << b.getId( ) << endl;
}