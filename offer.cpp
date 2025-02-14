#include <iostream>
#include <rtc/rtc.hpp>

int main() {
    rtc::InitLogger(rtc::LogLevel::Debug); // Incia um ambiente para depuração
    auto pc = std::make_shared<rtc::PeerConnection>();
}
