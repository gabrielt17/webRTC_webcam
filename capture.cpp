#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/video.hpp>

int main() {
    cv::VideoCapture cam(0); // Essa linha tem um classe que inicializa a minha câmera
    if (!cam.isOpened()) { // Caso a câmera seja inicializada corretamente, esse bloco não irá rodar
        std::cout << "Camera não incializada" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame; // Isso inicializa um matriz n-dimensional para guardar cada quadro da minha câmera
        cam.read(frame); // Pego os quadros que minha câmera está gerando e coloco dentro da matriz que criei
        if (frame.empty()) break; // Caso a câmera não escreva nada na matriz, paro o programa
        cv::imshow("Video", frame); // Cria uma janela para mostrar o frame que criei com o nome "Video"

        if (cv::waitKey(1) >= 0); br
    }

}