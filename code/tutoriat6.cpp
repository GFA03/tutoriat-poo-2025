#include <iostream>
#include <vector>
using namespace std;

class Animal {
protected:
    int varsta;
    string nume;
    int nrPicioare;
public:
    // Constructors
    Animal();
    Animal(int varsta, string nume, int nrPicioare);
    // Methods
    virtual void sunet();
    // Destructor
    virtual ~Animal();
};

class Carnivor : virtual public Animal {    // Here the keyword 'virtual' solves the diamond problem
private:
    string hrana;
public:
    // Constructors
    Carnivor();
    Carnivor(int varsta, string nume, int nrPicioare, string hrana);
    // Methods
    void sunet() override;  // Here we REDEFINE the behaviour of the method
    void mananc();          // instead of inheriting it from the parent
    // Destructor           // The keyword 'override' is optional, but its nice to have
    ~Carnivor();
};

class Erbivor : virtual public Animal { // Here the keyword 'virtual' solves the diamond problem
private:
    string tipIarba;
public:
    // Constructors
    Erbivor();
    Erbivor(int varsta, string nume, int nrPicioare, string tipIarba);
    // Methods
    void sunet() override;  // Same as in the Carnivor class
    // Destructor
    ~Erbivor();
};

class Omnivor : public Carnivor, public Erbivor {
/*
 * Here's how the inheritance looks like.           With the virtual inheritances from Carnivor and Erbivor
 *              Animal                                           Animal
 *             /      \                                        /   |   \
 *            /        \                                      /    |    \
 *       Carnivor     Erbivor                             Carnivor |    Erbivor
 *            \        /                                      \    |    /
 *             \      /                                        \   |   /
 *              Omnivor                                          Omnivor
 *                                                  More about that in the materials
 * */
private:
    float dinti;
public:
    Omnivor();
    void sunet() override;
    ~Omnivor();
};


/* You may be required to have 'an interactive menu' to your project
 * This class will help us tie everything together
 *  !!! IMPORTANT: This class won't count for the required number from the assignment !!!
 *           But will be really handy later :3
 * */
class Meniu {
private:
    // Here we'll hold the objects that will take part in out program
    vector<Animal*> animalutele = {};
public:
    /*
     * NOTE: Methods should serve only one purpose !!!
     *  Don't make a huge method that does many things
     *  like add objects, modifies them, prints them...
     *  It just does everything more complex, hard to
     *  read and debug, also you may need that bit of
     *  code in some other place, DONT COPY PASTE THAT,
     *  make a method and call it in both places :)
     * */
    // create a new animal and add it to the list
    void adaugaAnimal();    // take a look inside

    // Destructor
    ~Meniu();
};

Animal::Animal() {
    this->nume = "necunoscut";
    this->varsta = 0;
    this->nrPicioare = 0;
    cout << "Constructor->Animal" << endl;
}

Animal::Animal(int varsta, string nume, int nrPicioare) {
    this->varsta = varsta;
    this->nume = nume;
    this->nrPicioare = nrPicioare;
    cout << "Animal cu parametri" << endl;
}

void Animal::sunet() {
    cout << "sunet de animal idk" << endl;
}

Animal::~Animal() {
    cout << "Animal Destructor\n";
}

Carnivor::Carnivor() : Animal() {
    this->hrana = "nu stiu";
    cout << "Constructor->Carnivor" << endl;
}

Carnivor::Carnivor(int varsta, string nume, int nrPicioare, string hrana) : Animal(varsta, nume, nrPicioare) {
    this->hrana = hrana;
    cout << "Carnivor cu parametri" << endl;
}

void Carnivor::sunet() {
    cout << " sunet de carnivor" << endl;
}

void Carnivor::mananc() {
    cout << "nom nom nom" << endl;
}

Carnivor::~Carnivor() {
    cout << "Carnivor Destructor\n";
}

Erbivor::Erbivor() : Animal() {
    this->tipIarba = "n/a";
    cout << "Constructor -> Erbivor" << endl;
}

Erbivor::Erbivor(int varsta, string nume, int nrPicioare, string tipIarba) : Animal(varsta, nume, nrPicioare) {
    this->tipIarba = tipIarba;
}

void Erbivor::sunet() {
    cout << "sunet de erbivor" << endl;
}

Erbivor::~Erbivor() {
    cout << "Erbivor Destructor" << endl;
}

Omnivor::Omnivor() : Carnivor(), Erbivor() {
    this->dinti = 0;
    cout << "Constructor -> Omnivor" << endl;
}

void Omnivor::sunet() {
    cout << " sunet de omnivor" << endl;
}

Omnivor::~Omnivor() {
    cout << "Omnivor Destructor" << endl;
}

void Meniu::adaugaAnimal() {
    // Prompt the user with the options
    cout << "Ce animal vrei?" << endl;
    cout << "1. Carnivor" << endl;
    cout << "2. Erbivor" << endl;
    cout << "3. Omnivor" << endl;

    int option;     // Usually declare this variable around the place it's used
    cin >> option;
    switch (option) {
        case 1:
            animalutele.push_back(new Carnivor());
            break; //don't forget to break after each case, it will go to the next one
        case 2:
            animalutele.push_back(new Erbivor());
            break;
        case 3:
            animalutele.push_back(new Omnivor());
            break;
        default:
            cout << "Nu exista optiunea" << endl; // you can address the rest of
                                                  // the cases with a try-catch,
                                                  // but default case does the trick
    }
}

Meniu::~Meniu(){
    for (auto animal: this->animalutele)
        delete animal;  // Deallocate each remaining object
    this->animalutele.clear(); // clear the vector so it no longer holds any pointer
}


int main() {
    vector<Animal*> animalutele;    // Here's our first example of polymorphism
    Erbivor iepure;                 // In this vector we'll hold references to all
    Carnivor tigru;                 // the animals, but the instance of the pointers

    animalutele.push_back(&iepure);       // we can add pointers to existing objects
    animalutele.push_back(&tigru);

    animalutele.push_back(new Erbivor()); // or we can add new objects directly
                                          // DONT FORGE TO DELETE THAT


    // Let's iterate this kind of vectors
    cout << "Using ranged based iteration (clean)" << endl;
    for (const auto &animal : animalutele) {
        if (animal)
            animal->sunet();
    }

    cout << "Using iterator based iteration (you have control over the container)" << endl;
    for (auto it = animalutele.begin(); it != animalutele.end(); ++it) {
        if (*it)
            (*it)->sunet();
    }

    cout << "Using index based iteration (only if you need indexes)" << endl;
    for (size_t i = 0; i < animalutele.size(); ++i) {
        if (animalutele[i])
            animalutele[i]->sunet();
    }

    // Test the menu
    Meniu meniu;
    meniu.adaugaAnimal();

    // Deallocate the objects
    for (auto animal: animalutele)  // Will this crash? Why do you think so?
        delete animal;                       // Why won't this work here?
    return 0;                                // HINT: Check how the objects are instantiated
}
