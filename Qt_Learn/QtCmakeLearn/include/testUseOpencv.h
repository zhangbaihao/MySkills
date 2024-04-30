#include <opencv2/opencv.hpp>

int testOpencvMain() {
    cv::Mat image = cv::imread("../../png/test.png"); // 加载图像
    if (image.empty()) {
        std::cout << "无法加载图像" << std::endl;
        return -1;
    }

    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); // 转换为灰度图像

    cv::Mat blurredImage;
    cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0); // 高斯模糊

    cv::Mat edges;
    cv::Canny(blurredImage, edges, 50, 150); // 边缘检测

    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);
    cv::namedWindow("Edges", cv::WINDOW_NORMAL);

    cv::imshow("Original Image", image);
    cv::imshow("Edges", edges);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}