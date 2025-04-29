#include <iostream>
#include <vector>
#include <typeinfo>
#include <cstring>
#include <algorithm>
using namespace std;

class InsufficientPointsException : public std::exception{
public:
    virtual const char* what() const throw(){
        return "puncte insuficient";
    }
};

class InvalidIdException : public std::exception{
    public:
        virtual const char* what() const throw(){
            return "id invalid";
        }
    };

class Item{
protected:
    const int id;
    static int counterId;
public:
    Item():id(counterId++){}
    virtual ~Item(){}

    // Getters
    int getId() const { return id; }

    virtual void print(ostream& os) const {
        os << "Item ID: " << this->id;
    }

    friend ostream& operator<<(ostream& os, const Item& item) {
        item.print(os);
        return os;
    }

    virtual const int getInitialCost() const = 0;
    virtual const int getCostUpgrade() const = 0;
    virtual void upgrade() = 0;
};
int Item::counterId = 1;


class Zid: public Item{
private:
    double lungime;
    double inaltime;
    double grosime;
public:
    Zid();

    void print(ostream& os) const {
        Item::print(os);
        os << ", Lungime: " << this->lungime << ", Inaltime: " << this->inaltime << ", Grosime: " << this->grosime;
    }

    friend ostream& operator<<(ostream& os, const Zid& zid) {
        zid.print(os);
        return os;
    }

    const int getInitialCost() const {
        return 300;
    }

    const int getCostUpgrade() const{
        return 100 * lungime * inaltime * grosime;
    }
    void upgrade() {
        lungime += 1;
        inaltime += 1;
        grosime += 1;
    }
};
Zid::Zid():Item(){
   lungime = 1;
    inaltime = 2;
   grosime = 0.5;
}

class Turn: public Item{
private:
    double putereLaser;
public:
    Turn();

    void print(ostream& os) const {
        Item::print(os);
        os << ", Putere Laser: " << this->putereLaser;
    }

    friend ostream& operator<<(ostream& os, const Turn& turn) {
        turn.print(os);
        return os;
    }

    const int getInitialCost() const {
        return 500;
    }

    const int getCostUpgrade() const{
        return 500 * putereLaser;
    }
    void upgrade() {
        putereLaser += 500;
    }
};
Turn::Turn():Item() {
    putereLaser = 1000;
}

class Robot: public Item{
protected:
    int damage;
    int nivel;
    int viata;
public:
    Robot();

    void print(ostream& os) const {
        Item::print(os);
        os << ", Damage: " << this->damage << ", Nivel: " << this->nivel << ", Viata: " << this->viata;
    }

    friend ostream& operator<<(ostream& os, const Robot& robot) {
        robot.print(os);
        return os;
    }
};
Robot::Robot():Item() {
    nivel = 1;
    damage = 100;
    viata = 100;
}

class RobotAerian: public Robot{
private:
    double autonomie;
public:
    RobotAerian();

    void print(ostream& os) const {
        Robot::print(os);
        os << ", Autonomie: " << this->autonomie;
    }

    friend ostream& operator<<(ostream& os, const RobotAerian& robot) {
        robot.print(os);
        return os;
    }

    const int getInitialCost() const {
        return 100;
    }

    const int getCostUpgrade() const{ 
        return 50 * autonomie;
    }
    void upgrade() {
        nivel += 1;
        damage += 25;
        autonomie += 1;
    }
};
RobotAerian::RobotAerian():Robot() {
    autonomie = 10;
}

class RobotTerestru: public Robot{
private:
    int nrGloante;
    bool scut;
public:
    RobotTerestru();

    void print(ostream& os) const {
        Robot::print(os);
        os << ", Nr Gloante: " << this->nrGloante << ", Are scut: " << scut;
    }

    friend ostream& operator<<(ostream& os, const RobotTerestru& robot) {
        robot.print(os);
        return os;
    }

    const int getInitialCost() const {
        return 50;
    }

    const int getCostUpgrade() const{
        return 10 * nrGloante;
    }
    void upgrade() {
        nrGloante += 100;
        nivel += 1;
        damage += 50;
        if (nivel == 5) {
            scut = 1;
            viata += 50;
        }
    }
};
RobotTerestru::RobotTerestru():Robot() {
    nrGloante = 500;
    scut = false;
}

class Inventar{
private:
    const int PUNCTE_VANZARE = 500;

    static Inventar* instance;
    vector<Item*> items;
    int puncte;

    Inventar();
    Inventar(const Inventar&);
    void operator=(const Inventar&);
public:
    ~Inventar();

    static Inventar& getInstance() {
        static Inventar instance;
        return instance;
    }

    // Getters
    int getPuncte() const { return puncte; }
    vector<Item*> getItems() const { return items; }

    // 1.
    void adaugaItem(Item* item);
    void afisareTot();
    void afisareCrescatorDupaCostUpgrade();
    void afisareRoboti();
    Item* gasesteItem(int id);
    void upgrade(int id);
    void sorteazaDupaUpgradeCost();
    void vinde(int id);
};

Inventar* Inventar::instance = nullptr;

Inventar::Inventar(){
    items = {};
    puncte = 50000;
}

Inventar::~Inventar(){
    for(int i = 0 ; i < items.size() ; i++)
        delete items[i];
}

void Inventar::adaugaItem(Item *item) {

    int cost = item->getInitialCost();

    if(this->puncte < cost) {
        throw InsufficientPointsException();
    }

    this->puncte -= cost;
    this->items.push_back(item);
}

Item* Inventar::gasesteItem(int id) {
    for(int i = 0 ; i < items.size() ; i++){
        if(items[i]->getId() == id){
            return items[i];
        }
    }
    throw InvalidIdException(); 
}

void Inventar::sorteazaDupaUpgradeCost() {
    sort(this->items.begin(), this->items.end(), [](Item* a, Item* b){
        return a->getCostUpgrade() < b->getCostUpgrade();
    });
}

void Inventar::afisareCrescatorDupaCostUpgrade() {
    this->sorteazaDupaUpgradeCost();
    for(int i = 0 ; i < items.size() ; i++)
        cout << items[i]->getId() << " " << items[i]->getCostUpgrade() << endl;
}

void Inventar::afisareTot(){
    for(int i = 0 ; i < items.size(); i++)
        cout << *items[i] << endl;
}

void Inventar::afisareRoboti() {
    for(int i = 0; i < items.size(); i++) {
        if (strcmp(typeid(*items[i]).name(), typeid(RobotAerian).name()) == 0 ||
            strcmp(typeid(*items[i]).name(), typeid(RobotTerestru).name()) == 0) {
                cout << typeid(*items[i]).name() << endl;
            }
    }
}

void Inventar::upgrade(int id) {
    Item* item = gasesteItem(id);
    int costUpgrade = item->getCostUpgrade();
    if (this->puncte < costUpgrade) {
        throw InsufficientPointsException();
    }
    this->puncte -= costUpgrade;
    item->upgrade();
}

void Inventar::vinde(int id) {
    Item* item = gasesteItem(id);
    items.erase(find(items.begin(), items.end(), item));
    this->puncte += this->PUNCTE_VANZARE;
}

int main(){
    Inventar& inventar = Inventar::getInstance();

    try{
        int i = 0;

        // Testare ca exceptia cu puncte insuficiente merge
        // while(i++ < 1000) {
        //     cout << inventar.getPuncte() << endl;
        //     inventar.adaugaItem(new Zid());
        // }

        inventar.adaugaItem(new RobotAerian());
        inventar.adaugaItem(new RobotTerestru());
        inventar.adaugaItem(new Zid());
        inventar.adaugaItem(new Turn());

        inventar.afisareTot();
        cout << endl;

        // infinite money glitch
        // i = 4;
        // while (i++ < 10000) {
        //     inventar.adaugaItem(new Zid());
        //     inventar.vinde(i);
        // }
        cout << inventar.getPuncte() << endl;

        inventar.afisareCrescatorDupaCostUpgrade();
        // inventar.upgrade(1);
        // inventar.upgrade(2);
        // inventar.upgrade(3);
        // inventar.upgrade(4);
        // inventar.vinde(1);
        // inventar.afisareRoboti();

        inventar.afisareTot();
    }catch(const InsufficientPointsException& e){
        cout << e.what() << endl;
    }catch(const InvalidIdException& e){
        cout << e.what() << endl;
    }catch(...) {
        cout << "eroare" << endl;
    }
}