#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/video.hpp>

int main() {
    cv::VideoCapture cam(0); // Essa linha tem um classe que inicializa a minha câmera
    if (!cam.isOpened()) { // Caso a câmera seja inicializada corretamente, esse bloco não irá rodar
        std::cout << "Camera não incializada" << std::endl;
        return -1;
    }

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE); // Cria uma janela com o nome "Video"

    while (true) {
        cv::Mat frame; // Isso inicializa um matriz n-dimensional para guardar cada quadro da minha câmera
        cam >> frame; // Pego os quadros que minha câmera está gerando e coloco dentro da matriz que criei
        if (frame.empty()) break; // Caso a câmera não escreva nada na matriz, paro o programa
        cv::imshow("Video", frame); // Cria uma janela para mostrar o frame que criei com o nome "Video"
        
        if (cv::waitKey(1) == 27) { // Para se a tecla ESC for pressionada 
            break;
        }

    }
    // 4. Liberar recursos
    cam.release(); // Destrutor do meu objeto camera
    cv::destroyAllWindows(); // Fecha as janelas abertas
}