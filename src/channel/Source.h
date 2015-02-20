/*
 * Source.h
 *
 *  Created on: Feb 20, 2015
 *      Author: johan
 */

#ifndef CHANNEL_SOURCE_H_
#define CHANNEL_SOURCE_H_

namespace channel {

template<typename MessageType>
class Source {
public:

    Source(
            std::mutex& mutex,
            std::condition_variable& condition,
            std::vector<MessageType>& messages) :
                    mutex_(mutex),
                    condition_(condition),
                    messages_(messages) {
    }

    std::vector<MessageType> takeWithin(const std::chrono::milliseconds dt) {

        std::unique_lock<std::mutex> lock(mutex_);

        if (messages_.empty())
            condition_.wait_for(lock, dt);

        std::vector<MessageType> out = std::move(messages_);
        messages_ = std::vector<MessageType>();

        return out;
    }

    std::vector<MessageType> takeNow() {

        std::unique_lock<std::mutex> lock(mutex_);

        std::vector<MessageType> out = std::move(messages_);
        messages_ = std::vector<MessageType>();

        return out;
    }

private:
    std::mutex& mutex_;
    std::condition_variable& condition_;
    std::vector<MessageType>& messages_;

    Source(const Source& other) = delete;
    Source& operator=(const Source& other) = delete;
};
} /* namespace channe */

#endif /* CHANNEL_SOURCE_H_ */
