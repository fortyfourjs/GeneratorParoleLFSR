#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PasswordConfig.h"
#include "LFSRPasswordGenerator.h"
#include <QMessageBox>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600,400);
    setMinimumSize(600,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGenerare_clicked()
{
    PasswordConfig config;
    config.min_alfabetice = ui->spinMinAlfabetice->value();
    config.max_alfabetice = ui->spinMaxAlfabetice->value();
    config.min_numerice = ui->spinMinCifre->value();
    config.max_numerice = ui->spinMaxCifre->value();
    config.min_speciale = ui->spinMinSpeciale->value();
    config.total_caractere = ui->spinTotalCaractere->value();
    config.nr_separator = ui->spinIntervalSeparator->value();

    if(!config.ValidareParola()){
        QMessageBox::critical(this, "Eroare validare", "Suma caracterelor minime depaseste lungimea totala sau lungimea este prea mica!");
            return;
    }
    std::unique_ptr<PasswordGenerator> generator = std::make_unique<LFSRPasswordGenerator>();
    std::string parola = generator->generate(config);

    ui->txtparola->setText(QString::fromStdString(parola));
}

