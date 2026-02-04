#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    static constexpr int KERNEL = 2;
    static constexpr int THRESHOLD = 30;
    static constexpr int BACKGROUND_COLOR = 50;
    static constexpr int MOVEMENT_COLOR = 100;
    static const std::string WINDOW_NAME = "Diff Threshold";

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    cv::Mat frame1, frame2, diff, gray, mask, output;
    cap >> frame1;
    if (frame1.empty()) return -1;


    cv::stackBlur(frame1, frame1, {KERNEL | 1, KERNEL | 1});
    cv::namedWindow(WINDOW_NAME, cv::WINDOW_NORMAL);

    while (true) {
        cap >> frame2;
        if (frame2.empty()) break;

        cv::stackBlur(frame2, frame2, {KERNEL | 1, KERNEL | 1});

        cv::absdiff(frame1, frame2, diff);
        cv::cvtColor(diff, gray, cv::COLOR_BGR2GRAY);
        cv::threshold(gray, mask, THRESHOLD, 255, cv::THRESH_BINARY);

        output = cv::Mat::ones(mask.size(), CV_8UC1) * BACKGROUND_COLOR;
        output.setTo(MOVEMENT_COLOR, mask);

        cv::imshow(WINDOW_NAME, output);

        frame2.copyTo(frame1);

        if (cv::waitKey(1) == 'q') break;
    }

    cv::destroyAllWindows();
    return 0;
}
