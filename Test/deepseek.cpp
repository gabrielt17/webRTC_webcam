#include <iostream>
#include <opencv2/opencv.hpp>
#include <rtc/rtc.hpp>

int main() {
    // 1. Configurar OpenCV
    cv::VideoCapture cam(0);
    if (!cam.isOpened()) {
        std::cerr << "Erro ao abrir a câmera" << std::endl;
        return -1;
    }

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

    // 2. Inicializar WebRTC
    rtc::InitLogger(rtc::LogLevel::Debug); // Habilita logs para depuração
    auto pc = std::make_shared<rtc::PeerConnection>();

    // 3. Configurar STUN (servidor público do Google)
    rtc::Configuration config;
    config.iceServers.emplace_back("stun:stun.l.google.com:19302");
    pc = std::make_shared<rtc::PeerConnection>(config);

    // 4. Adicionar vídeo track
    auto videoTrack = pc->addTrack(rtc::Description::Video("video"));

    // 5. Configurar sinalização (exemplo simplificado)
    pc->onLocalDescription([&](rtc::Description sdp) {
        std::cout << "SDP Offer:\n" << sdp << std::endl;
    });

    pc->onLocalCandidate([&](rtc::Candidate candidate) {
        std::cout << "ICE Candidate: " << candidate << std::endl;
    });

    // 6. Loop para capturar e exibir frames
    while (true) {
        cv::Mat frame;
        cam >> frame;
        if (frame.empty()) break;

        cv::imshow("Video", frame);

        // 7. Enviar frames via WebRTC (exemplo simplificado)
        // Aqui você precisará converter o frame para um formato compatível (ex: I420)
        // e enviá-lo via videoTrack->send(...).

        if (cv::waitKey(1) == 27) { // Tecla ESC para sair
            break;
        }
    }

    // 8. Liberar recursos
    cam.release();
    cv::destroyAllWindows();
    return 0;
}