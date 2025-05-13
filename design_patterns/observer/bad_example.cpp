#include <iostream>
#include <string>
#include <vector>

// --- Tightly coupled Display classes ---
// These specific display types are known by the sensor
class PhoneDisplay {
private:
    std::string id;
public:
    PhoneDisplay(std::string id) : id(id) {}
    void updateTemperature(float temp) { // Specific update method
        std::cout << "PhoneDisplay [" << id << "]: Temperature is now " << temp << " C" << std::endl;
        // ... phone specific rendering ...
    }
};

class WebsiteWidget {
public:
    void refreshWeatherData(float temp, float humidity) { // Different update method signature!
        std::cout << "WebsiteWidget: Updating weather data. Temp: " << temp << " C" << std::endl;
         // ... website specific rendering ... (ignoring humidity for simplicity here)
    }
};
// --- The "Subject" knows concrete "Observers" ---
class WeatherSensor {
private:
    float currentTemperature;
    // Direct references to specific observer objects - TIGHT COUPLING!
    PhoneDisplay* phoneDisplay1;
    PhoneDisplay* phoneDisplay2;
    WebsiteWidget* websiteWidget;

public:
    // Constructor requires passing specific displays
    WeatherSensor(PhoneDisplay* pd1, PhoneDisplay* pd2, WebsiteWidget* ww) :
        currentTemperature(0.0f), phoneDisplay1(pd1), phoneDisplay2(pd2), websiteWidget(ww) {}

    void setTemperature(float temp) {
        if (temp != currentTemperature) {
            std::cout << "\nSensor: Temperature changed to " << temp << " C. Notifying displays..." << std::endl;
            currentTemperature = temp;

            // Manually call update methods on each known display
            // Problem: Different update methods! Must know details of each display.
            if (phoneDisplay1) {
                phoneDisplay1->updateTemperature(currentTemperature);
            }
            if (phoneDisplay2) {
                phoneDisplay2->updateTemperature(currentTemperature);
            }
            if (websiteWidget) {
                 // Need to pass humidity too, even if not used by all displays? Problematic.
                websiteWidget->refreshWeatherData(currentTemperature, 60.0f); // Dummy humidity
            }
        }
    }
     // Problem: Adding a new type of display (e.g., DesktopApp) requires modifying
     // this WeatherSensor class (add member, update constructor, update setTemperature).
};

int main() {
    // Create the specific display objects first
    PhoneDisplay phone1("MyPhone");
    PhoneDisplay phone2("WorkPhone");
    WebsiteWidget website;

    // Sensor needs to know about all displays at construction
    WeatherSensor sensor(&phone1, &phone2, &website);

    sensor.setTemperature(25.5f);
    sensor.setTemperature(26.1f);

    // Problem: What if phone2 is destroyed? The sensor holds a dangling pointer.
    // Problem: How to add/remove displays dynamically? Requires complex logic in Sensor.

    return 0;
}