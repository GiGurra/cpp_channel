/*
 * Channel.h
 *
 *  Created on: Feb 20, 2015
 *      Author: johan
 */

#ifndef CPP_CHANNEL_CHANNEL_H_
#define CPP_CHANNEL_CHANNEL_H_

#include <channel/Sink.h>
#include <channel/Source.h>

namespace channel {

template<typename MessageType>
class Channel {
public:
    Channel() :
                    source_(mutex_, condition_, messages_),
                    sink_(mutex_, condition_, messages_) {
    }

    Source<MessageType>& source() {
        return source_;
    }

    Sink<MessageType>& sink() {
        return sink_;
    }

private:
    std::mutex mutex_;
    std::condition_variable condition_;
    std::vector<MessageType> messages_;
    Source<MessageType> source_;
    Sink<MessageType> sink_;

    Channel(const Channel& other) = delete;
    Channel& operator=(const Channel& other) = delete;
};

}

#endif /* CPP_CHANNEL_CHANNEL_H_ */
