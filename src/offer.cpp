#include <iostream>
#include <opencv2/opencv.hpp>
#include <rtc/rtc.hpp>

int main(){
    cv::VideoCapture cam(0);
    if (!cam.isOpened()) {
        std::cout << "Deu pau no câmera" << std::endl;
    }

    rtc::InitLogger(rtc::LogLevel::Debug);

    rtc::Configuration config;
    config.iceServers.emplace_back("stun:stun.l.google.com:19302");
    auto peer = std::make_shared<rtc::PeerConnection>(config);

    auto videoTrack = peer->addTrack(rtc::Description::Video("video"));

    peer->onLocalDescription([&](rtc::Description sdp) {
        std::cout << "Meu sdp: \n" << sdp << std::endl;
    });

    peer->onLocalCandidate([&](rtc::Candidate candidate) {
        std::cout << "Meu ICE: \n" << candidate << std::endl;
    });
}