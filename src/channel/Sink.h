/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Johan Kjölhede
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef CHANNEL_SINK_H_
#define CHANNEL_SINK_H_

#include <condition_variable>
#include <vector>
#include <mutex>

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
