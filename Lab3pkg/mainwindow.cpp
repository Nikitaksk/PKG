#include "mainwindow.h"
#include "transformation.h"
#include "filter_kernel.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QApplication>
#include <QPaintEvent>
#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"




//Реализация высокочастотных фильтров (увеличение резкости)

//Глобальная пороговая обработка (2 метода на выбор)+ Адаптивная пороговая обработка

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *mainLayout = new QGridLayout(this->centralWidget());
    mainLayout->addWidget(ui->directoryEntriesList, 0, 0, Qt::AlignLeft);

    PaintingAreaWidget *paintAreaWidget = new PaintingAreaWidget();

    mainLayout->addWidget(ui->widget, 0, 1, 1, 4);


    mainLayout->addWidget( ui->loadFolderButton, 1, 0);
    mainLayout->addWidget( ui->pushButton, 1, 1);
    mainLayout->addWidget( ui->pushButton_2, 1, 2);
    mainLayout->addWidget( ui->pushButton_3, 1, 3);
    mainLayout->addWidget( ui->pushButton_4, 1, 4);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFolderButton_clicked() {
    currentDirectory = QDir(
        QFileDialog::getExistingDirectory(
            nullptr, "Open Directory...", "/",
            QFileDialog::ShowDirsOnly
        )
    );

    ui->directoryEntriesList->clear();
    QStringList temp = currentDirectory.entryList();
    for (QString s : temp) {
        bool file_is_supported = false;
        for (QString extension : supportedExtensions) {
            if (s.endsWith(extension, Qt::CaseInsensitive)) {
                file_is_supported = true;
                break;
            }
        }

        if (file_is_supported) {
            ui->directoryEntriesList->addItem(s);
        }
    }

}


void MainWindow::on_directoryEntriesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    QImage tempImage = QImage(currentDirectory.absoluteFilePath(current->text()));
    tempImage.convertTo(QImage::Format_RGB32);
    ui->widget->setCurrentImage(tempImage);
    currentImage = tempImage;
}


void MainWindow::on_pushButton_clicked() {
    currentImage.convertTo(QImage::Format_Grayscale8);





//    cv::Mat input_matrix = transformation::mat_from_qimage(currentImage), output_matrix;
    cv::Mat input_matrix = cv::Mat(currentImage.height(), currentImage.width(), CV_8U, currentImage.bits(), currentImage.bytesPerLine()), output_matrix;
    filter2D( input_matrix, output_matrix, -1, filter_kernel_const::NINEFILTER.to_cv_Mat());
//    currentImage = transformation::qimage_from_mat(output_matrix);
    QImage temp((uchar*) output_matrix.data, output_matrix.cols, output_matrix.rows, output_matrix.step, QImage::Format_Grayscale8);
    ui->widget->setCurrentImage(temp);

}

void MainWindow::on_pushButton_2_clicked() {
    currentImage.convertTo(QImage::Format_Grayscale8);
    cv::Mat input_matrix = cv::Mat(currentImage.height(), currentImage.width(), CV_8U, currentImage.bits(), currentImage.bytesPerLine()), output_matrix;
    cv::adaptiveThreshold(input_matrix, output_matrix, 255, cv::AdaptiveThresholdTypes::ADAPTIVE_THRESH_MEAN_C, cv::ThresholdTypes::THRESH_BINARY, 3, 2);
    QImage temp((uchar*) output_matrix.data, output_matrix.cols, output_matrix.rows, output_matrix.step, QImage::Format_Grayscale8);
    ui->widget->setCurrentImage(temp);
}


void MainWindow::on_pushButton_3_clicked() {
    currentImage.convertTo(QImage::Format_Grayscale8);
    cv::Mat input_matrix = cv::Mat(currentImage.height(), currentImage.width(), CV_8U, currentImage.bits(), currentImage.bytesPerLine()), output_matrix;
    cv::threshold(input_matrix, output_matrix, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
    QImage temp((uchar*) output_matrix.data, output_matrix.cols, output_matrix.rows, output_matrix.step, QImage::Format_Grayscale8);
    ui->widget->setCurrentImage(temp);
}

int MainWindow::getHistogramThreshold(const cv::Mat& cvsrc) {
    int prev = 0, cur = 10;
    const int eps = 5;
    int u[2];

    //calculate histogram manually
    int hist[256] = {0};
    for(int i = 0; i < cvsrc.rows; ++i)
        for(int j = 0; j < cvsrc.cols; ++j)
        {
            ++hist[cvsrc.at<uchar>(i,j)];
        }

    long long sums[256], cnts[256];
    sums[0] = 0;
    cnts[0] = hist[0];
    for (int i = 1; i < 256; ++i)
    {
        sums[i] = sums[i - 1] + hist[i] * i;
        cnts[i] = cnts[i - 1] + hist[i];
    }

    while(std::abs<int>(cur - prev) > eps)
    {
        u[0] = sums[cur] / (std::max(cnts[cur], 1LL));
        u[1] = (sums[255] - sums[cur]) / (std::max(cnts[255] - cnts[cur], 1LL));
        prev = cur;
        cur = (u[0] + u[1]) / 2;
    }
    return cur;
}


void MainWindow::on_pushButton_4_clicked() {
    currentImage.convertTo(QImage::Format_Grayscale8);
    cv::Mat input_matrix = cv::Mat(currentImage.height(), currentImage.width(), CV_8U, currentImage.bits(), currentImage.bytesPerLine()), output_matrix;
    cv::threshold(input_matrix, output_matrix, getHistogramThreshold(input_matrix), 255, cv::THRESH_BINARY);
    QImage temp((uchar*) output_matrix.data, output_matrix.cols, output_matrix.rows, output_matrix.step, QImage::Format_Grayscale8);
    ui->widget->setCurrentImage(temp);
}


