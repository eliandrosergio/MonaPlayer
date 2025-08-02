#include "mainwindow.hpp"

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->sliderTempoMovendo = false;
    this->arquivo = "";

    this->player = new QMediaPlayer(this);
    this->player->setVolume(44);

    connect(player, &QMediaPlayer::volumeChanged, this, &MainWindow::updateSliderVolume);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSliderTempoPos);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateSliderTempoDur);
}

// Destructor
MainWindow::~MainWindow()
{
    delete this->player;
    delete this->ui;
}

// ==================================== UI funcs ====================================

void MainWindow::on_sliderVolume_valueChanged(int value)
{
    this->setVolume(value);
}

void MainWindow::on_btnEscolher_Musica_clicked()
{
    this->escolher_musica();
}

void MainWindow::on_actionAbrir_arquivo_triggered()
{
    this->escolher_musica();
}

void MainWindow::on_btnTocar_Pausar_clicked()
{
    this->tocar_pausar();
}

void MainWindow::on_actionTocar_Pausar_triggered()
{
    this->tocar_pausar();
}

void MainWindow::on_sliderTempo_sliderPressed()
{
    this->sliderTempoMovendo = true;
}

void MainWindow::on_sliderTempo_sliderReleased()
{
    this->sliderTempoMovendo = false;
    this->setPosicao(this->ui->sliderTempo->value());
}

void MainWindow::on_actionAumentar_Volume_10_triggered()
{
    this->setVolume(this->player->volume() + 10);
}

void MainWindow::on_actionDiminuir_Volume_10_triggered()
{
    this->setVolume(this->player->volume() - 10);
}

void MainWindow::on_sliderTempo_sliderMoved(int position)
{
    this->ui->lblTempo_Atual->setText(this->mudar_lblTempo(position));
}

void MainWindow::on_actionSobre_triggered()
{

}

void MainWindow::on_actionCreditos_triggered()
{

}
