#ifndef RADIO_QUEUE_H
#define RADIO_QUEUE_H

#include <queue>

#include "ProtoWriteBuffer.h"
#include "config.h"

using namespace std;

#define MAX_QUEUE_ELEM 20 // 20*50 = 1kB bytes of memory - a problematic scenario

class RadioQueue {
   public:
    void Reset() {
        while(!messageQueue.empty()) {
            messageQueue.pop();
        }
    }

    void Enqueue(LORA_MSG_TEMPLATE& message) {
        ProtoWriteBuffer buffer;
        buffer.clear();

        if (messageQueue.size() > MAX_QUEUE_ELEM) {
            // throw "Queue overrun";
            return;
        }

        message.serialize(buffer);
        messageQueue.push(buffer);
    }

    void Dequeue() {
        messageQueue.pop();
    }

    bool HasNext() {
        return messageQueue.size() > 0;
    }

    ProtoWriteBuffer& GetNext() {
        return messageQueue.front();
    }

   private:
    queue<ProtoWriteBuffer> messageQueue;
};

#endif  // RADIO_QUEUE_H
