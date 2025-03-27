#include <iostream>
#include <cstring>

using namespace std;

class Calculator {
    private:
    static int counter_id;
    const int id = counter_id;                                               
    string procesor;                                                         
    char* versiune;             // New attribute
    int ram;
    bool placa_video;
    
    public:
    // Constructors 
    Calculator();
    Calculator(string procesor, bool placa_video, int ram, char* versiune);
    Calculator(string procesor);                      
    Calculator(const Calculator& obj);
    // Operators
    Calculator& operator=(const Calculator& obj);
    Calculator operator+(const Calculator& obj);
    
    // Getters
    int getId()const{return this->id;}
    int getRam()const{return this->ram;}
    // Setters
    // Methods
    // Static Methods
    static void functie(){
        counter_id = 10;
        cout<<counter_id;
    }

    ~Calculator();
};
 
int Calculator::counter_id = 1;

Calculator::Calculator():id(counter_id++){   
    this->versiune = new char[strlen("default") + 1];           // Make the pointer 'look' in a new place of the length of our default message. + 1 for '\0'
    strcpy(this->versiune, "default");                          // Copy the message 'default' in the new space

    this->procesor = "unknown";                                 
    this->placa_video = true;                                  
    this->ram = 8;                                              
}

Calculator::Calculator(string procesor):id(counter_id++){       
    this->versiune = new char[strlen("default") + 1];           // Make the pointer 'look' in a new place of the length of our default message. + 1 for '\0'
    strcpy(this->versiune, "default");                          // Copy the message 'default' in the new space

    this->procesor = procesor;                                  
    this->placa_video = false;
    this->ram = 100000;
}

Calculator::Calculator(string procesor, bool placa_video, int ram, char* versiune):id(counter_id++){
    this->versiune = new char[strlen(versiune) + 1];            // Make the pointer 'look' in a new place of the length of our parameter message. + 1 for '\0'
    strcpy(this->versiune, versiune);                           // Copy the parameter message in the new space

    this->procesor = procesor;                                  
    this->placa_video = placa_video;                            
    this->ram = ram;                                           
}                                                               

Calculator::Calculator(const Calculator& obj):id(counter_id++){
    this->versiune = new char[strlen(obj.versiune) + 1];       // Make the pointer 'look' in a new place of the length of the other object's message. + 1 for '\0'
    strcpy(this->versiune, obj.versiune);                      // Copy the other object's message in the new space

    // this->versiune = obj.versiune;                          // DON'T without a good reason, both the pointers will 'look' at the same memory
                                                               // Deleting from one will affect the other one.
    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
}

Calculator::~Calculator(){
    if(this->versiune != nullptr){          // Check if it's not pointing at NULL
        delete[] this->versiune;            // Delete the pointer
        this->versiune = nullptr;           // Set it back to NULL for safety
    }
}

Calculator& Calculator::operator=(const Calculator& obj){
    if (this == &obj)                                           
        return *this;
    
    // this->versiune = obj.versiune;                          // DON'T without a good reason, both the pointers will 'look' at the same memory
                                                               // Deleting from one will affect the other one.

    if (this->versiune != nullptr){                            // Our current object is already allocated so there is a value here so
        delete[] this->versiune;                               // we safely delete it
        this->versiune = nullptr;
    }

    this->versiune = new char[strlen(obj.versiune) + 1];       // Copy the value just like in the copy constructor
    strcpy(this->versiune, obj.versiune);

    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
    return *this;                                               
}

Calculator Calculator::operator+(const Calculator& obj){        // The + operator doesn't change the operands
    Calculator temp = *this;                                    // Make a copy to any of them 

    temp.ram += obj.ram;                                        // Apply the changes to any of them
    temp.procesor += obj.procesor;  
                                                                // NOTE: you can perform any operations here, not only addition
                                                                //       also you can return any desired type
    return temp;
}

int main(){
    Calculator x;
 
    cout << (x + x).getRam() << endl;
    cout<< x.getRam() << endl;
    cout <<((x + x) + x).getRam() << endl;
    cout <<(x + (x + x)).getRam() << endl;
}
