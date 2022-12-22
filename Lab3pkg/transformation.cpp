#include "transformation.h"

cv::Mat transformation::mat_from_qimage(const QImage &image)
{
    return cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits());
}
cv::Mat transformation::mat_from_qimageGray(const QImage &image)
{
    return cv::Mat(image.height(), image.width(), CV_8U, (void*)image.bits());
}

QImage transformation::qimage_from_mat(const cv::Mat &mat)
{
    int DATA_SIZE = CV_8UC4 * mat.size().height * mat.size().width;
    unsigned char *data = new unsigned char[DATA_SIZE];
    memcpy(data, mat.ptr(), DATA_SIZE);
    return QImage(data, mat.size().width, mat.size().height, QImage::Format_RGB32);
}

QImage transformation::qimage_from_matGray(const cv::Mat &mat)
{
    int DATA_SIZE = CV_8U * mat.size().height * mat.size().width;
    unsigned char *data = new unsigned char[DATA_SIZE];
    memcpy(data, mat.ptr(), DATA_SIZE);
    return QImage(data, mat.size().width, mat.size().height, QImage::Format_Grayscale8);
}
