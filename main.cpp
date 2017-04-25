// RIKS++
#include "hyker/riks/riks_whitelist.hpp"
#include "hyker/riks/rikskit.hpp"
#include "hyker/riks/message/message.hpp"

// Cryptobox++
#include "hyker/cryptobox/cryptobox.hpp"
#include "hyker/security/security_util.hpp"

// Toolbox++
#include "hyker/values.hpp"
#include "hyker/json.hpp"

// std
#include <iostream>
#include <string>
#include <utility>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Pinger {
public:
    hyker::riks::RiksKit m_riks1;
    hyker::riks::RiksKit m_riks2;
    int s = 0;
    
    Pinger(const std::string& riks1, const std::string& riks2) :
            m_riks1 (initRiksKit(riks1)),
            m_riks2 (initRiksKit(riks2)) {
        std::cout << m_riks1.getUID() << " - " << m_riks2.getUID() << std::endl;
    }

    void ping(const hyker::riks::Message& message) {
        std::cout << "Encrypting " << std::to_string(++s) << std::endl;
        
        m_riks1.encryptMessage(message, "namespace", [&](const std::string& encrypted) {
            std::cout << "Decrypting " << std::to_string(++s) << std::endl;
            m_riks2.decryptMessage(encrypted,
                                   [&](const hyker::riks::Message& decrypted) {
                                       ping(decrypted);
                                   },
                                   [](hyker::Exception& e) {
                                       std::cout << "Error: " << e.what() << std::endl;
                                   });
        });
    }

    hyker::cryptobox::Cryptobox initCryptobox() {
        return hyker::cryptobox::Cryptobox('#' + hyker::cryptobox::SecurityUtil::generateString(10), "asdqwe");
    }

    hyker::riks::RiksWhitelist initRiksWhitelist() {
        return hyker::riks::RiksWhitelist([](const std::string& uid, const std::string& messageNamespace, const std::string& keyID) -> bool {
            return true;
        });
    }

    hyker::riks::RiksKit initRiksKit(const std::string& file) {
        auto rikskit = [&]() {
            try {
                return hyker::riks::RiksKit::load(file, "asdqwe", initRiksWhitelist());
            } catch (...) {
                return hyker::riks::RiksKit(initCryptobox(), initRiksWhitelist());
            }
        }();

        sleep(1);

        return rikskit;
    }

};

int main() {

    auto file1 = "riks1a.cache";
    auto file2 = "riks1b.cache";

    Pinger pinger(file1, file2);

    sleep(1);

    pinger.ping(hyker::riks::Message("this is secret", "this is immutable", "this is mutable"));

    sleep(10);

    pinger.m_riks1.save(file1, "asdqwe");
    pinger.m_riks2.save(file2, "asdqwe");

    sleep(1000);
    return 0;
}
