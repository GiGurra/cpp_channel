#include <iostream>
#include <string>

#include <channel/Channel.h>

using namespace channel;
using namespace std;

int main() {

    Channel<string> channel;
    auto& sink = channel.sink();
    auto& source = channel.source();

    sink.give("abcde");
    sink.give("12345");
    sink.give("hehe");
    sink.give("öä+");

    auto msgs1 = source.takeWithin(std::chrono::milliseconds(1));

    sink.give("wglalala");
    sink.give("1aeh2345");
    sink.give("heaeg4he");
    sink.give("öä+ga4");

    auto msgs2 = source.takeNow();

    for (const auto& msgs : { msgs1, msgs2 })
        for (const auto& msg : msgs)
            cout << msg << endl;

    return 0;
}

