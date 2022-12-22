#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QImage>
#include <opencv2/core/mat.hpp>

namespace transformation
{
    cv::Mat mat_from_qimage(const QImage &image);
    cv::Mat mat_from_qimageGray(const QImage &image);
    QImage qimage_from_mat(const cv::Mat &mat);
    QImage qimage_from_matGray(const cv::Mat &mat);
}


#endif // TRANSFORMATION_H
