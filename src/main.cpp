#include <iostream>

#include "RDParser.h"
#include "CountVisitor.h"

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            RDParser parser(line);
            auto astTree = parser.parse();
            CountVisitor visitor;
            visitor.visit(*astTree);
            std::cout << "Result is: " << visitor.getResult() << std::endl;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}