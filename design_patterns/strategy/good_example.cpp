#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

// 1. Define the Strategy Interface
class RouteStrategy {
public:
    virtual ~RouteStrategy() = default; // Virtual destructor
    virtual void calculate(const std::string& origin, const std::string& destination) = 0;
};

// 2. Implement Concrete Strategies
class FastestRoute : public RouteStrategy {
public:
    void calculate(const std::string& origin, const std::string& destination) override {
        std::cout << "Strategy: Calculating the FASTEST route (avoiding traffic, using highways)." << std::endl;
        // ... complex logic for fastest route ...
    }
};

class ShortestRoute : public RouteStrategy {
public:
    void calculate(const std::string& origin, const std::string& destination) override {
         std::cout << "Strategy: Calculating the SHORTEST route (minimizing distance)." << std::endl;
        // ... complex logic for shortest route ...
    }
};

class ScenicRoute : public RouteStrategy {
public:
    void calculate(const std::string& origin, const std::string& destination) override {
        std::cout << "Strategy: Calculating the most SCENIC route (prioritizing views, avoiding highways)." << std::endl;
        // ... complex logic for scenic route ...
    }
};

// 3. Define the Context class that uses a Strategy
class Navigator {
private:
    // Holds a reference to the current strategy object
    std::unique_ptr<RouteStrategy> strategy;

public:
    // Constructor takes an initial strategy
    Navigator(std::unique_ptr<RouteStrategy> initialStrategy) : strategy(std::move(initialStrategy)) {}

    // Allows changing the strategy at runtime
    void setStrategy(std::unique_ptr<RouteStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    // Delegates the work to the current strategy object
    void calculateRoute(const std::string& origin, const std::string& destination) {
        std::cout << "Calculating route from " << origin << " to " << destination << std::endl;
        if (strategy) {
            strategy->calculate(origin, destination); // Delegate!
            std::cout << "Route calculated." << std::endl;
        } else {
            std::cout << "Error: No strategy set!" << std::endl;
        }
    }
};

int main() {
    // Start with the Fastest strategy
    Navigator navigator(std::make_unique<FastestRoute>());
    navigator.calculateRoute("Home", "Work");

    std::cout << "\nChanging strategy...\n";
    // Switch to the Scenic strategy
    navigator.setStrategy(std::make_unique<ScenicRoute>());
    navigator.calculateRoute("Home", "Park");

    std::cout << "\nChanging strategy...\n";
    // Switch to the Shortest strategy
    navigator.setStrategy(std::make_unique<ShortestRoute>());
    navigator.calculateRoute("Work", "Home");

    // Benefit: Adding a new strategy (e.g., EconomicRoute) only requires creating
    // a new class derived from RouteStrategy. The Navigator class doesn't change.

    return 0;
}