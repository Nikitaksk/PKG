#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <QListWidgetItem>
#include <QListWidget>
#include <transformation.h>
#include <filter_kernel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDir currentDirectory;
    QString currentFilePath;
    QImage currentImage;


    std::array<QString, 7> supportedExtensions = {
        ".jpg"  ,
        ".jpeg" ,
        ".tif"  ,
        ".tiff" ,
        ".gif"  ,
        ".bmp"  ,
        ".png"  ,
    };

private:
    Ui::MainWindow *ui;

private slots:
    void on_loadFolderButton_clicked();

    void on_directoryEntriesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

protected:
    int getHistogramThreshold(const cv::Mat& cvsrc);

};
#endif // MAINWINDOW_H
