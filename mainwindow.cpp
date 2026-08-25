#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PasswordConfig.h"
#include "LFSRPasswordGenerator.h"
#include <QMessageBox>
#include <memory>
#include "PasswordSaver.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ComplexitateParola.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinTotalCaractere->setValue(12);
    ui->spinMinAlfabetice->setValue(1);
    ui->spinMaxAlfabetice->setValue(12);
    ui->spinMinCifre->setValue(1);
    ui->spinMaxCifre->setValue(12);
    ui->spinMinSpeciale->setValue(1);
    ui->spinMaxSpeciale->setValue((12));
    ui->spinIntervalSeparator->setValue(0);
    ui->spin_nrParole->setValue(1);
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
    config.max_speciale = ui->spinMaxSpeciale->value();
    config.total_caractere = ui->spinTotalCaractere->value();
    config.nr_separator = ui->spinIntervalSeparator->value();
    config.nr_parole = ui->spin_nrParole->value();

    if(!config.ValidareParola()){
        QMessageBox::critical(this, "Eroare validare", "Suma caracterelor minime depaseste lungimea totala sau lungimea este prea mica!");
            return;
    }
    ui->txtparola->clear();
    std::unique_ptr<PasswordGenerator> generator = std::make_unique<LFSRPasswordGenerator>();
    std::string ultimaParola = "";
    for(int i=0;i<config.nr_parole;i++){
        std::string parola = generator->generate(config);
        QString NumerotareParole = QString("%1. %2")
                                       .arg(i+1)
                                       .arg(QString::fromStdString(parola));
        ui->txtparola->append(NumerotareParole);
        ultimaParola = parola;
    }
    if(!ultimaParola.empty()){
        auto nivel_complexitate = PasswordValidator::evaluateStrength(ultimaParola);
        std::string complexitate_str = PasswordValidator::strengthToString(nivel_complexitate);

        actualizeazaSemafor(complexitate_str);

    }
}
void MainWindow::on_btnSalvare_clicked(){
    QString continut = ui->txtparola->toPlainText();
    if(continut.isEmpty()){
        QMessageBox::warning(this, "Atentie!","Nu exista nicio parola salvata");
        return;
    }
    QString caleFisier = QFileDialog::getSaveFileName(
        this,
        "Salveaza parolele",
        "Parole.txt",
        "Fisiere Text(*.txt);;;Toate fisierele(*)");
    if(caleFisier.isEmpty()){
        return;
    }
    PasswordSaver::saveFile(caleFisier.toStdString(), continut.toStdString());
    QMessageBox::information(this, "Succes","Parolele au fost salvate!");

}
void MainWindow::actualizeazaSemafor(const std::string& nivel){
    QString stilGri = "background-color:#bdc3c7; border-radius = 3px;";
    QString stilRosu = "background-color:#e74c3c; border-radius = 3px;";
    QString stilGalben = "background-color:#f1c40f; border-radius = 3px;";
    QString stilVerde = "background-color:#2ecc71; border-radius = 3px;";

    if(nivel == "Slaba"){
        ui->label_semafor1->setStyleSheet(stilRosu);
        ui->label_semafor2->setStyleSheet(stilGri);
        ui->label_semafor3->setStyleSheet(stilGri);
    }
    else if(nivel == "Medie"){
        ui->label_semafor1->setStyleSheet(stilGalben);
        ui->label_semafor2->setStyleSheet(stilGalben);
        ui->label_semafor3->setStyleSheet(stilGri);
    }
    else if(nivel == "Puternica"){
            ui->label_semafor1->setStyleSheet(stilVerde);
            ui->label_semafor2->setStyleSheet(stilVerde);
            ui->label_semafor3->setStyleSheet(stilVerde);
        }
    else{
        ui->label_semafor1->setStyleSheet(stilGri);
        ui->label_semafor2->setStyleSheet(stilGri);
        ui->label_semafor3->setStyleSheet(stilGri);
        }
}

