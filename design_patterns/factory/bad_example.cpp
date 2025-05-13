// Let's model transportation.
// We can transport packages over seas by ship, by land by car or bike, or by air by plane.

#include <iostream>

class Transport {
public:
    virtual void deliver() = 0; 
};

class LandTransport : public Transport {
public:
    virtual void onTheRoad() = 0; 
};

class Car : public LandTransport {
public:
    void deliver() override {
        std::cout << "Delivering by car" << std::endl;
    }
    void onTheRoad() override {
        std::cout << "Driving on one way" << std::endl;
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
};

class Plane : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by plane" << std::endl;
    }
};

class Ship : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by ship" << std::endl;
    }
};

int main() {
    Transport* transport1 = new Car();
    transport1->deliver();
    LandTransport* landTransport1 = dynamic_cast<LandTransport*>(transport1);
    if (landTransport1) {
        landTransport1->onTheRoad();
    }

    Transport* transport2 = new Bike();
    transport2->deliver();
    LandTransport* landTransport2 = dynamic_cast<LandTransport*>(transport2);
    if (landTransport2) {
        landTransport2->onTheRoad();
    }

    Transport* transport3 = new Plane();
    transport3->deliver();

    Transport* transport4 = new Ship();
    transport4->deliver();

    delete transport1;
    delete transport2;
    delete transport3;
    delete transport4;

    return 0;
}