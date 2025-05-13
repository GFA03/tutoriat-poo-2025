#include <iostream>
#include <string>
#include <vector>
#include <memory> // Using raw pointers for simplicity, but note lifetime issues
#include <algorithm> // For std::remove

// 1. Define the Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature) = 0; // Common update method
};

// 2. Define the Subject Interface (or often an Abstract Class)
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// 3. Implement Concrete Subject
class WeatherSensor : public Subject {
private:
    std::vector<Observer*> observers; // Holds generic Observers
    float currentTemperature;

public:
    WeatherSensor() : currentTemperature(0.0f) {}

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        // Find and remove the observer (C++20 has std::erase)
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        std::cout << "Sensor: Notifying " << observers.size() << " observers..." << std::endl;
        // Call the common update method on all registered observers
        for (Observer* observer : observers) {
            if (observer) { // Good practice to check pointers
                observer->update(currentTemperature);
            }
        }
    }

    // Business logic that triggers notification
    void setTemperature(float temp) {
        if (temp != currentTemperature) {
             std::cout << "\nSensor: Temperature changed to " << temp << " C." << std::endl;
            currentTemperature = temp;
            notify(); // Notify all observers about the change
        }
    }

    float getTemperature() const {
        return currentTemperature;
    }
};

// 4. Implement Concrete Observers
class PhoneDisplay : public Observer {
private:
    std::string id;
    Subject* subject; // Optional: reference back to subject to pull data if needed

public:
    PhoneDisplay(std::string id, Subject* sub) : id(id), subject(sub) {
        subject->attach(this); // Register with the subject upon creation
        std::cout << "PhoneDisplay [" << id << "] created and attached." << std::endl;
    }
     ~PhoneDisplay() override {
         if(subject) subject->detach(this); // Unregister when destroyed
         std::cout << "PhoneDisplay [" << id << "] detached and destroyed." << std::endl;
     }

    void update(float temperature) override {
         // Could also pull data: float temp = static_cast<WeatherSensor*>(subject)->getTemperature();
        std::cout << "PhoneDisplay [" << id << "]: Temperature is now " << temperature << " C" << std::endl;
        // ... phone specific rendering ...
    }
};

class WebsiteWidget : public Observer {
private:
    Subject* subject;
public:
     WebsiteWidget(Subject* sub) : subject(sub) {
         subject->attach(this);
         std::cout << "WebsiteWidget created and attached." << std::endl;
     }
     ~WebsiteWidget() override {
         if(subject) subject->detach(this);
         std::cout << "WebsiteWidget detached and destroyed." << std::endl;
     }

    void update(float temperature) override {
        std::cout << "WebsiteWidget: Updating weather data. Temp: " << temperature << " C" << std::endl;
        // ... website specific rendering ...
    }
};


int main() {
    WeatherSensor sensor; // The Subject

    // Create observers and attach them dynamically
    PhoneDisplay phone1("MyPhone", &sensor);
    WebsiteWidget website(&sensor);

    sensor.setTemperature(25.5f);

    { // Scope for another observer
        PhoneDisplay phone2("WorkPhone", &sensor);
        sensor.setTemperature(26.1f);
        // phone2 goes out of scope here, its destructor detaches it
         std::cout << "WorkPhone observer going out of scope...\n";
    } // Destructor of phone2 is called, detaching it from sensor

    sensor.setTemperature(27.0f); // Only phone1 and website are notified


    // Note on Lifetime Management: This example uses raw pointers for simplicity.
    // In real applications, managing the lifetime of observers and ensuring the
    // subject doesn't hold dangling pointers is crucial. Using smart pointers
    // (like std::weak_ptr for observers held by the subject) or other
    // registration mechanisms might be necessary.

    return 0;
}