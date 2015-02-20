/*
 * Sink.h
 *
 *  Created on: Feb 20, 2015
 *      Author: johan
 */

#ifndef CHANNEL_SINK_H_
#define CHANNEL_SINK_H_

namespace channel {

template<typename MessageType>
class Sink {
public:

    Sink(
            std::mutex& mutex,
            std::condition_variable& condition,
            std::vector<MessageType>& messages) :
                    mutex_(mutex),
                    condition_(condition),
                    messages_(messages) {
    }

    void give(MessageType msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        messages_.push_back(std::move(msg));
        condition_.notify_all();
    }

private:
    std::mutex& mutex_;
    std::condition_variable& condition_;
    std::vector<MessageType>& messages_;

    Sink(const Sink& other) = delete;
    Sink& operator=(const Sink& other) = delete;
};

} /* namespace channe */

#endif /* CHANNEL_SINK_H_ */
