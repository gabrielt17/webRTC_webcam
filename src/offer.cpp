#include <iostream>
#include <opencv2/opencv.hpp>
#include <rtc/rtc.hpp>

int main(){
    cv::VideoCapture cam(0);
    if (!cam.isOpened()) {
        std::cout << "A câmera não funcionou" << std::endl;
    }

    rtc::InitLogger(rtc::LogLevel::Debug);

    rtc::Configuration config;
    config.iceServers.emplace_back("stun:stun.l.google.com:19302");
    auto peer = std::make_shared<rtc::PeerConnection>(config);

    auto videoTrack = peer->addTrack(rtc::Description::Video("video"));

    peer->onLocalDescription([&](rtc::Description sdp) {
        std::cout << "Meu SDP: \n" << sdp <<  std::endl;
    });

    peer->onLocalCandidate([&](rtc::Candidate candidate) {
        std::cout << "Meu ICE: \n" << candidate << std::endl;
    });

    std::string sdpAnswer;
    std::cout << "Cole a SDP Answer do receptor aqui: ";
    std::getline(std::cin, sdpAnswer);
    peer->setRemoteDescription(rtc::Description(sdpAnswer, "answer"));

    std::string iceCandidate;
    std::cout << "Cole o ICE Candidate do receptor aqui: ";
    std::getline(std::cin, iceCandidate);
    peer->addRemoteCandidate(rtc::Candidate(iceCandidate));

    while (true) {
        cv::Mat frame;
        cam >> frame;
        if (frame.empty()) break;
        cv::imshow("Video", frame);

        // Aqui você precisará converter `frame` para um formato compatível com WebRTC e enviá-lo via `videoTrack->send(...)`
        
        if (cv::waitKey(1) == 27) break;
    }

    cam.release();
    cv::destroyAllWindows();
    return 0;
}