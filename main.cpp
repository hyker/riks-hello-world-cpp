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
    Pinger(std::string file_1, std::string file_2) :
        m_file_1    (file_1),
        m_file_2    (file_2),
        m_rikskit_1 (initRiksKit(file_1)),
        m_rikskit_2 (initRiksKit(file_2)) {
        
        std::cout << m_rikskit_1.getUID() << " - " << m_rikskit_2.getUID() << std::endl;
        
        sleep(1);
        
        ping(hyker::riks::Message("this is secret", "this is immutable", "this is mutable"));
    }

    ~Pinger() {
        m_rikskit_1.save(m_file_1, "asdqwe");
        m_rikskit_2.save(m_file_2, "asdqwe");
    }

private:
    std::string m_file_1;
    std::string m_file_2;
    
    hyker::riks::RiksKit m_rikskit_1;
    hyker::riks::RiksKit m_rikskit_2;

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

    hyker::cryptobox::Cryptobox initCryptobox() {
        return hyker::cryptobox::Cryptobox('#' + hyker::cryptobox::SecurityUtil::generateString(10), "asdqwe");
    }

    hyker::riks::RiksWhitelist initRiksWhitelist() {
        return hyker::riks::RiksWhitelist([](const std::string& uid, const std::string& message_namespace, const std::string& key_id) -> bool {
            return true;
        });
    }

    void ping(const hyker::riks::Message& message) {
        static int index = 0;
        
        std::cout << "Encrypting " << std::to_string(++index) << std::endl;
        
        m_rikskit_1.encryptMessage(message, "namespace", [&](const std::string& encrypted) {
            std::cout << "Decrypting " << std::to_string(++index) << std::endl;
            
            m_rikskit_2.decryptMessage(encrypted,
                                   [&](const hyker::riks::Message& decrypted) {
                                       ping(decrypted);
                                   },
                                   [](hyker::Exception& e) {
                                       std::cout << "Error: " << e.what() << std::endl;
                                   });
        });
    }

};

int main() {
    Pinger pinger("riks1a.cache", "riks1b.cache");
    sleep(1000);
    return 0;
}
