#include <thread>
#include <queue>
#include "../../utils/tlp.h"
#include "endpoint_app.h"
#include "../../utils/queue_wrapper.h"

class PacketListener {
public:
    PacketListener(QueueWrapper<std::queue<TLP>>& queueWrapper, EndpointApp& endpointApp)
        : queueWrapper_(queueWrapper)
        , endpointApp_(endpointApp)
    {
    }

    void start() {
        thread_ = std::thread([this]() {
            while (true) {
                std::queue<TLP> packetQueue = queueWrapper_.pop();
                endpointApp_.receivePackets(packetQueue);
            }
        });
    }

    void stop() {
        thread_.join();
    }

private:
    QueueWrapper<std::queue<TLP>>& queueWrapper_;
    EndpointApp& endpointApp_;
    std::thread thread_;
};
