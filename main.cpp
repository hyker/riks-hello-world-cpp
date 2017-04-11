// RIKS++
#include "apptimate/riks/riks_whitelist.hpp"
#include "apptimate/riks/rikskit.hpp"
#include "apptimate/riks/message/message.hpp"

// Cryptobox++
#include "apptimate/cryptobox/cryptobox.hpp"
#include "apptimate/security/security_util.hpp"

// Toolbox++
#include "apptimate/values.hpp"
#include "apptimate/json.hpp"

// std
#include <iostream>
#include <string>
#include <utility>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Pinger {
public:
    Pinger(apptimate::riks::RiksKit&& riks1, apptimate::riks::RiksKit&& riks2) :
            m_riks1 (std::move(riks1)),
            m_riks2 (std::move(riks2)) {
        std::cout << m_riks1.getUID() << " - " << m_riks2.getUID() << std::endl;
    }

    void ping(const apptimate::riks::Message& message) {
        std::cout << "Encrypting " << std::to_string(++s) << std::endl;
        m_riks1.encryptMessage(message, "namespace", [&](const std::string& encrypted) {
            std::cout << "Decrypting " << std::to_string(++s) << std::endl;
            m_riks2.decryptMessage(encrypted,
                                   [&](const apptimate::riks::Message& decrypted) {
                                       ping(decrypted);
                                   },
                                   [](apptimate::Exception& e) {
                                       std::cout << "Error: " << e.what() << std::endl;
                                   });
        });
    }

    int s = 0;
    apptimate::riks::RiksKit m_riks1;
    apptimate::riks::RiksKit m_riks2;
};

apptimate::cryptobox::Cryptobox initCryptobox() {
    return apptimate::cryptobox::Cryptobox('#' + apptimate::cryptobox::SecurityUtil::generateString(10), "asdqwe");
}

apptimate::riks::RiksWhitelist initRiksWhitelist() {
    return apptimate::riks::RiksWhitelist(
            [](const std::string& uid, const std::string& messageNamespace, const std::string& keyID) -> bool {
                return true;
            }
    );
}

apptimate::riks::RiksKit initRiksKit(const std::string& file) {
    auto rikskit = [&](){
        try {
            return apptimate::riks::RiksKit::load(file, "asdqwe", initRiksWhitelist());
        } catch (...) {
            return apptimate::riks::RiksKit(initCryptobox(), initRiksWhitelist());
        }
    }();
    sleep(1);
    return rikskit;
}

int main() {

    auto file1 = "riks1a.cache";
    auto file2 = "riks1b.cache";

    Pinger pinger(initRiksKit(file1), initRiksKit(file2));

    sleep(1);

    pinger.ping(apptimate::riks::Message("this is secret", "this is immutable", "this is mutable"));

    sleep(10);

    pinger.m_riks1.save(file1, "asdqwe");
    pinger.m_riks2.save(file2, "asdqwe");

    sleep(1000);
    return 0;
}
