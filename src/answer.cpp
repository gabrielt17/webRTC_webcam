#include <iostream>
#include <opencv2/opencv.hpp>
#include <rtc/rtc.hpp>

int main() {
    // 1. Inicializa o logger do WebRTC (para depuração)
    rtc::InitLogger(rtc::LogLevel::Debug);

    // 2. Configuração do PeerConnection
    rtc::Configuration config;
    config.iceServers.emplace_back("stun:stun.l.google.com:19302"); // Servidor STUN
    auto peer = std::make_shared<rtc::PeerConnection>(config);

    // 3. Callback para a resposta SDP
    peer->onLocalDescription([&](rtc::Description sdp) {
        std::cout << "Resposta SDP:\n" << sdp << std::endl;
    });

    // 4. Callback para os candidatos ICE
    peer->onLocalCandidate([&](rtc::Candidate candidate) {
        std::cout << "Candidato ICE:\n" << candidate << std::endl;
    });

    // 5. Recebe a oferta SDP do transmissor
    std::string sdpOffer;
    std::cout << "Cole a oferta SDP do transmissor aqui: ";
    std::getline(std::cin, sdpOffer);
    peer->setRemoteDescription(rtc::Description(sdpOffer, "offer"));

    // 6. Cria a resposta SDP
    peer->setLocalDescription();

    // 7. Recebe os candidatos ICE do transmissor
    std::string iceCandidate;
    std::cout << "Cole o ICE Candidate do transmissor aqui: ";
    std::getline(std::cin, iceCandidate);
    peer->addRemoteCandidate(rtc::Candidate(iceCandidate));

    // 8. Callback para receber frames de vídeo
    peer->onTrack([&](std::shared_ptr<rtc::Track> track) {
        std::cout << "Track recebida: " << track->mid() << std::endl;

        track->onMessage([&](rtc::binary message) {
            // Aqui você processaria os frames de vídeo recebidos
            // Exemplo: decodificar e exibir com OpenCV
            std::cout << "Frame recebido (" << message.size() << " bytes)" << std::endl;
        });
    });

    // 9. Mantém o programa rodando
    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.ignore();

    return 0;
}