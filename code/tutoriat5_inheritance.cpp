//
// Created by Mihai on 4/1/2025.
//
#include <iostream>
#include <cstring>
using namespace std;

// First we make a simple class, really general
// There are many kinds of animals we can place in categories
// eg: terrestrial, aquatic, bugs idk

// Here we want a base class that has the common attributes
class Animal{
protected:
    // those are just to exemplify, dont mind the logic too much
    int varsta;
    string nume;
    int nrPicioare;

    public:
    Animal();
    Animal(int varsta, string nume, int nrPicioare);

    void sound(){
        cout << "au" << endl;
    };

    ~Animal(){ cout<< "Animal Destructor\n";}

};

// Here we make a more specific class, 'Carnivor'
// A carnivore is also an animal so it should have
// all it's attributes, right?
class Carnivor: public Animal{
private:
    // we must add something new to it, that makes it
    // more specific
    string hrana;       // again, dont mind the example
public:
    Carnivor():Animal(){    // here, in the initilizaion list we denote
                            // the things we inherit we will populate with
                            // that constructor
        this->hrana = "nu stiu";
        cout<<"Constructor->Carnivor" << endl;
    }
    Carnivor(int varsta, string nume, int nrPicioare, string hrana): Animal(varsta, nume, nrPicioare){
        // here again, we used the constructor from Animal and reduced
        // the quantity of code with a lot
        this->hrana = hrana;       // but we need to populate the new attribute
        cout<<"Carnivor cu parametri"<< endl;
    }
    // here we OVERRIDE the sound method from Animal
    // we give it 'a new meaning'
    // our more specific kind of animal does a more specific sound right?
    void sound(){
        cout<<" mrrrrr" << endl;
    }

    ~Carnivor(){cout<<"Carnivor Destructor\n";}
};


Animal::Animal() {
    this->nume = "necunoscut";
    this->varsta = 0;
    this->nrPicioare = 0;
    cout<<"Constructor->Animal" << endl;
}

Animal::Animal(int varsta, string nume, int nrPicioare){
    this->varsta = varsta;
    this->nume = nume;
    this->nrPicioare = nrPicioare;
    cout<<"Animal cu parametri" << endl;
}

int main(){
    // What will this print? Why?
    Animal furnica(0, "andrei", 6);
    Carnivor caine(2, "gioni", 4, "copii");
    furnica.sound();
    caine.sound();
}
