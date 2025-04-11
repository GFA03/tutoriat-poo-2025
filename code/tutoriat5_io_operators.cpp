#include <iostream>
#include <cstring>


using namespace std;

class Calculator {
private:
    static int counter_id;
    const int id = counter_id;
    string procesor;
    char* versiune;             
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

    // For all operators, the 'this' is the lefthand operand
    // in the case of IO operators you COULD write as any other
    // operator but you ll be forced to call it "x << cout" which
    // is cursed

    // Our this in this case is not the one in left so we must make
    // the operand 'friend' with our class so that it can access
    // private attributes
    friend ostream& operator<<(ostream& out, const Calculator& obj);
    friend istream& operator>>(istream& in, Calculator& obj);

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
    this->versiune = new char[strlen("default") + 1];
    strcpy(this->versiune, "default");

    this->procesor = "unknown";
    this->placa_video = true;
    this->ram = 8;
}

Calculator::Calculator(string procesor):id(counter_id++){
    this->versiune = new char[strlen("default") + 1];
    strcpy(this->versiune, "default");

    this->procesor = procesor;
    this->placa_video = false;
    this->ram = 100000;
}

Calculator::Calculator(string procesor, bool placa_video, int ram, char* versiune):id(counter_id++){
    this->versiune = new char[strlen(versiune) + 1];
    strcpy(this->versiune, versiune);

    this->procesor = procesor;
    this->placa_video = placa_video;
    this->ram = ram;
}

Calculator::Calculator(const Calculator& obj):id(counter_id++){
    this->versiune = new char[strlen(obj.versiune) + 1];
    strcpy(this->versiune, obj.versiune);

    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
}

Calculator::~Calculator(){

    if(this->versiune != nullptr){
        delete[] this->versiune;
        this->versiune = nullptr;
    }
}

Calculator& Calculator::operator=(const Calculator& obj){
    if (this == &obj)
        return *this;

    if (this->versiune != nullptr){
        delete[] this->versiune;
        this->versiune = nullptr;
    }

    this->versiune = new char[strlen(obj.versiune) + 1];
    strcpy(this->versiune, obj.versiune);

    this->procesor = obj.procesor;
    this->placa_video = obj.placa_video;
    this->ram = obj.ram;
    return *this;
}

Calculator Calculator::operator+(const Calculator& obj){
    Calculator temp = *this;

    temp.ram += obj.ram;
    temp.procesor += obj.procesor;
    return temp;
}

istream& operator>>(istream& in, Calculator &obj){
    // we must assume the dynamically allocated memory is already there
    // so we cant just overwrite it

    // 1st we read inside a buffer
    char versiuneNou[255];
    cout<<"Versiune: "; in>>versiuneNou;
    // 2nd we free the already existing memory
    if(obj.versiune != nullptr)
        delete[] obj.versiune;
    // 3rd we copy allocate new space for the char*
    obj.versiune = new char[strlen(versiuneNou+1)];
    // 4th we copy the content from the buffer
    strcpy(obj.versiune, versiuneNou);

    // regular stuff here
    cout<<"Procesor: ";in>>obj.procesor;
    cout<<"Ram: "; in>>obj.ram;
    cout<<"Placa Video: "; in>>obj.placa_video;
    return in;
}

std::ostream& operator<<(ostream& out, const Calculator& obj){
    out << "Id: " << obj.id << '\n';
    out<< "Procesor: " << obj.procesor << '\n';
    out << "Versiune: " << obj.versiune << '\n';

    // why do we return ostream and istream? recall operator=
    return out;
}

int main(){
    Calculator x;

}
