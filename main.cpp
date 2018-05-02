#include "hyker/delegate_client.hpp"
#include "hyker/exception.hpp"
#include "hyker/log.hpp"

#include <iostream>
#include <string>
#include <thread>

int main() {
    try {
        const hyker::DelegateClient delegate_client{
            "key-delegate",
            1234,
            "72019E5042C24C90D23091ED74272360",
            false,
            "UNTRUSTED_API_KEY"
        };

        const auto token = "199005157756";

        { // Preregister
        const auto session = delegate_client.open();
        const auto result = session.preregister(token);
        std::cout << result.dump(4) << '\n';
        }

        { // Collect
        const auto session = delegate_client.open();
        const auto result = session.collect(token);
        std::cout << result.dump(4) << '\n';
        }

    } catch (hyker::Exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

}
