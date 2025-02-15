#include <iostream>
#include <rtc/rtc.hpp>
#include <opencv2/opencv.hpp>

int main() {

    cv::VideoCapture cam(0); // Essa linha tem um classe que inicializa a minha câmera
    if (!cam.isOpened()) { // Caso a câmera seja inicializada corretamente, esse bloco não irá rodar
        std::cout << "Camera não incializada" << std::endl;
        return -1;
    }

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE); // Cria uma janela com o nome "Video"

    // Configurações iniciais
    rtc::InitLogger(rtc::LogLevel::Debug); // Incia um ambiente para depuração

    // Configurações para o STUN
    rtc::Configuration config; // Inicia um objeto na stack para configurar a ICE
    config.iceServers.emplace_back("stun:stun.l.google.com:19302"); // "Dá append" à lista de servidores STUN
    auto pc = std::make_shared<rtc::PeerConnection>(config); // Cria um objeto da classe PeerConnection na heap com as configurações da ICE

    // Passando a stream de video da minha webcam para envio
    auto camstream = pc->addTrack(rtc::Description::Video("video"));

    // Criando a oferta local (SDP Local)
    pc->onLocalDescription([&](rtc::Description sdp){ std::cout << "SDP Offer:\n" << sdp << std::endl;});

    // Criando espaço para receber respostas (SDP Remoto)
    pc->onLocalCandidate([&](rtc::Candidate candidate){ std::cout << "SDP Answer:\n" << candidate << std::endl;});

    while (true) {
        cv::Mat frame; // Isso inicializa um matriz n-dimensional para guardar cada quadro da minha câmera
        cam >> frame; // Pego os quadros que minha câmera está gerando e coloco dentro da matriz que criei
        if (frame.empty()) break; // Caso a câmera não escreva nada na matriz, paro o programa
        cv::imshow("Video", frame); // Cria uma janela para mostrar o frame que criei com o nome "Video"
        
        if (cv::waitKey(1) == 27) break; // Para se a tecla ESC for pressionada 

    }

    // Liberar recursos
    cam.release(); // Destrutor do meu objeto camera
    cv::destroyAllWindows(); // Fecha as janelas abertas
}
