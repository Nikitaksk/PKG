#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <set>
#include <iostream>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::map<QString, QString> compression;

    QTableWidget *mainTable;

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


private slots:
    void on_openFolderButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
