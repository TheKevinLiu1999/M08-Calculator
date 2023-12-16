#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

// Enum for operation types
enum class OperationType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};

// Base class for arithmetic operations
class Operation {
public:
    virtual double performOperation(double operand1, double operand2) const = 0;
    virtual OperationType getOperationType() const = 0;
    virtual ~Operation() {}
};

// Derived classes for specific operations
class AdditionOperation : public Operation {
public:
    double performOperation(double operand1, double operand2) const override {
        return operand1 + operand2;
    }

    OperationType getOperationType() const override {
        return OperationType::ADDITION;
    }
};

class SubtractionOperation : public Operation {
public:
    double performOperation(double operand1, double operand2) const override {
        return operand1 - operand2;
    }

    OperationType getOperationType() const override {
        return OperationType::SUBTRACTION;
    }
};

class MultiplicationOperation : public Operation {
public:
    double performOperation(double operand1, double operand2) const override {
        return operand1 * operand2;
    }

    OperationType getOperationType() const override {
        return OperationType::MULTIPLICATION;
    }
};

class DivisionOperation : public Operation {
public:
    double performOperation(double operand1, double operand2) const override {
        if (operand2 == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return operand1 / operand2;
    }

    OperationType getOperationType() const override {
        return OperationType::DIVISION;
    }
};

// Calculator class that uses composition to perform operations
class Calculator {
private:
    Operation* operation;

public:
    Calculator(Operation* op) : operation(op) {}

    double calculate(double operand1, double operand2) const {
        return operation->performOperation(operand1, operand2);
    }

    OperationType getOperationType() const {
        return operation->getOperationType();
    }
};

int main() {
    try {
        // Create calculator with addition operation
        Calculator calculator(new AdditionOperation);

        // Create calculator with subtraction operation
        Calculator calculator1(new SubtractionOperation);
  
        // Create calculator with multiplication operation
        Calculator calculator2(new MultiplicationOperation);
  
        // Create calculator with division operation
        Calculator calculator3(new DivisionOperation);

        // Get input from the user
        double operand1, operand2;
        std::cout << "Enter two numbers: ";
        std::cin >> operand1 >> operand2;
        std:: string op;                      // Doesn't work
        std::cout << "Enter operation (+, -, *, /): ";
        std::cin >> op;

        // Perform calculation 
        double result = calculator.calculate(operand1, operand2);

        // Display result
        std::cout << "Result: " << result << std::endl;

        // Save result to a file
        std::ofstream outputFile("result.txt");
        if (outputFile.is_open()) {
            outputFile << "Result: " << result << std::endl;
            outputFile.close();
        } else {
            std::cerr << "Error opening file for writing" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
    
}
