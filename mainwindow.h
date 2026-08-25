#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGenerare_clicked();
    void on_btnSalvare_clicked();

private:
    Ui::MainWindow *ui;
    void actualizeazaSemafor(const std::string& nivel);
};

#endif // MAINWINDOW_H
