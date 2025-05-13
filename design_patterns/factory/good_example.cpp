// Let's model transportation using a factory pattern.
// We can transport packages over seas by ship, by land by car or bike, or by air by plane.

#include <iostream>
#include <memory>


// O clasa abstracta de Transport pe care toate mijloacele de transport o mostenesc
class Transport {
public:
    virtual void deliver() = 0;
};

// Sa spunem ca avem un business logic masiv pentru transporturile pe uscat
// si vrem sa adaugam o noua metoda pentru a calcula eficienta consumului de combustibil
class LandTransport : public Transport {
public:
    virtual void onTheRoad() = 0;
    virtual int calculateGasEfficiency() = 0;
};

// Pe uscat putem transporta cu masina sau bicicleta
class Car : public LandTransport {
public:
    void deliver() override {
        std::cout << "Delivering by car" << std::endl;
    }

    void onTheRoad() override {
        std::cout << "Driving on one way" << std::endl;
    }
    int calculateGasEfficiency() override {
        return 20;
    }
};

class Bike : public LandTransport {
public:
    void deliver() override {
        std::cout << "Delivering by bike" << std::endl;
    }

    void onTheRoad() override {
        std::cout << "Keep on ridin'!" << std::endl;
    }

    int calculateGasEfficiency() override {
        return 0;
    }
};

// In aer putem transporta cu avionul
class Plane : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by plane" << std::endl;
    }
};

// Pe apa putem transporta cu vaporul
class Ship : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by ship" << std::endl;
    }
};

// Factory pattern: lasam clientul sa decida ce tip de transport vrea
// si ii dam un factory care sa creeze transportul dorit
// Factory abstractizeaza tipul concret de transport (adica nu stie ce transport va fi creat)
class TransportFactory {
public:
    virtual std::unique_ptr<Transport> createTransport() = 0;
};

// Fiecare mijloc de transport are un factory propriu
class CarFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Car>();
    }    
};

class BikeFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Bike>();
    }
};

class PlaneFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Plane>();
    }
};

class ShipFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Ship>();
    }
};

int main() {
    // Acum a ramas sa verificam ce mijloc de transport vrem sa cream
    // si sa cream factory-ul corespunzator
    std::unique_ptr<TransportFactory> factory1 = std::make_unique<CarFactory>();
    std::unique_ptr<Transport> transport1 = factory1->createTransport();
    transport1->deliver();

    std::unique_ptr<TransportFactory> factory2 = std::make_unique<BikeFactory>();
    std::unique_ptr<Transport> transport2 = factory2->createTransport();
    transport2->deliver();

    return 0;
}