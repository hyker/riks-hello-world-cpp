#include "hyker/outbox.hpp"
#include "hyker/rikskit.hpp"
#include "hyker/log.hpp"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int main() {
    try {
        using namespace hyker;
        using namespace hyker::outbox;
        using namespace hyker::riks;

        const std::string uid = "cpp-0018";
        const std::string uid_friend = "java-0018";

        RiksKit rikskit(uid, "asdqwe", {[](std::string uid, std::string message_namespace, std::string key_id) {
            return true;
        }});

        Outbox outbox(uid + "-outbox", "dev.msg.hykr.io", 1443, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        outbox.attachInbox({[&](const Data& payload, const Json&) {
            std::cout << (std::string)payload  << '\n';
            outbox.put(uid_friend + "-outbox", payload);
        }});
        outbox.start();
        outbox.put(uid_friend + "-outbox", rikskit.encryptMessage({"some secret data", "some immutable plaintext", "some mutable plaintext"}, "namespace"));

        std::condition_variable cv;
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);
    } catch (hyker::Exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}
