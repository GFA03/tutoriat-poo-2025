#include <iostream>
#include <string>
#include <vector> // Included for potential route data, though simplified here

// Enum to define navigation modes
enum class NavigationMode {
    FASTEST,
    SHORTEST,
    SCENIC
};

// The class with hardcoded strategies
class Navigator {
private:
    NavigationMode mode;

public:
    Navigator(NavigationMode initialMode = NavigationMode::FASTEST) : mode(initialMode) {}

    void setMode(NavigationMode newMode) {
        mode = newMode;
    }

    // This method becomes complex and hard to modify
    void calculateRoute(const std::string& origin, const std::string& destination) {
        std::cout << "Calculating route from " << origin << " to " << destination << std::endl;

        // Huge conditional block based on the mode
        if (mode == NavigationMode::FASTEST) {
            std::cout << "Strategy: Calculating the FASTEST route (avoiding traffic, using highways)." << std::endl;
            // ... complex logic for fastest route ...
        } else if (mode == NavigationMode::SHORTEST) {
            std::cout << "Strategy: Calculating the SHORTEST route (minimizing distance)." << std::endl;
            // ... complex logic for shortest route ...
        } else if (mode == NavigationMode::SCENIC) {
            std::cout << "Strategy: Calculating the most SCENIC route (prioritizing views, avoiding highways)." << std::endl;
            // ... complex logic for scenic route ...
        } else {
            std::cout << "Error: Unknown navigation mode!" << std::endl;
        }
        std::cout << "Route calculated." << std::endl;
    }
};

int main() {
    Navigator navigator(NavigationMode::FASTEST);
    navigator.calculateRoute("Home", "Work");

    std::cout << "\nChanging strategy...\n";
    navigator.setMode(NavigationMode::SCENIC);
    navigator.calculateRoute("Home", "Park");

     // Problem: Adding a new strategy (e.g., "ECONOMIC") requires modifying the
     // Navigator::calculateRoute method, violating Open/Closed Principle.
     // The method can become very large and hard to test/maintain.

    return 0;
}