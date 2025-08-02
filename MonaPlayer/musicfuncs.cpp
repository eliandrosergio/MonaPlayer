#include "mainwindow.hpp"

// ================================== Debug ==================================

void    MainWindow::printMsg( const string & msg ) {
    cout << "[Eliandro] " << msg << endl;
    return ;
}

// ================================== Player ==================================

bool    MainWindow::setArquivo( void ) {
    QString arquivo = QFileDialog::getOpenFileName(nullptr, "Selecione um arquivo", "", "Arquivos MP3 (*.mp3)");
    bool estado = false;

    if (!arquivo.isEmpty()) {
        this->arquivo = arquivo;
        this->player->setMedia(QUrl::fromLocalFile(arquivo));
        if (this->tocar_pausarMusica() == 1) estado = true;
        this->printMsg("Arquivo de música trocado.");
    } else this->printMsg("Arquivo de música vazio.");
    return (estado);
}

void    MainWindow::setVolume( int valor ) {
    if (valor < 0) valor = 0;
    else if (valor > 100) valor = 100;
    this->player->setVolume(valor);
    this->printMsg( "Volume da música alterado para: " + num_to_string(valor));
    return ;
}

int    MainWindow::tocar_pausarMusica( void ) {
    if (!this->arquivo.isEmpty()) {
        QMediaPlayer::State estado = this->player->state();

        if (estado == QMediaPlayer::PlayingState) {
            this->player->pause();
            return (0);
        } else if (estado == QMediaPlayer::PausedState) {
            this->player->play();
            return (1);
        } else if (estado == QMediaPlayer::StoppedState) {
            this->player->setMedia(QUrl::fromLocalFile(this->arquivo));
            this->player->play();
            return (1);
        }
    }
    return (2);
}

void    MainWindow::setPosicao( int valor ) {
    int tempo = this->player->duration();

    if (valor < 0) valor = 0;
    else if (valor > tempo) valor = tempo;
    this->player->setPosition(valor);
    this->printMsg("Posição alterada para: " + num_to_string(valor));
}

// ==================================== UI AUX funcs ====================================

void    MainWindow::updateSliderVolume( int volume ) {
    QString volumeStr;

    if (volume < 10) volumeStr = "00";
    else if (volume < 100) volumeStr = "0";
    volumeStr += QString::number(volume);
    this->ui->sliderVolume->setValue(volume);
    this->ui->lblVolume->setText(volumeStr + "%");
}

void    MainWindow::updateSliderTempoPos( qint64 posicao ) {
    if (!this->sliderTempoMovendo) {
        this->ui->sliderTempo->setValue(posicao);
        this->ui->lblTempo_Atual->setText(this->mudar_lblTempo(posicao));
    }
}

void    MainWindow::updateSliderTempoDur( qint64 duracao ) {
    this->ui->sliderTempo->setMaximum(duracao);
    this->ui->lblTempo_Total->setText(this->mudar_lblTempo(duracao));
}

void    MainWindow::escolher_musica( void ) {
    if (this->setArquivo()) {
        this->ui->btnTocar_Pausar->setText("Pausar");
        this->ui->actionTocar_Pausar->setText("Pausar");
        this->ui->statusbar->showMessage(this->arquivo);
    }
}

void    MainWindow::tocar_pausar( void ) {
    int estado = this->tocar_pausarMusica();

    if (estado == 1) {
        this->ui->btnTocar_Pausar->setText("Pausar");
        this->ui->actionTocar_Pausar->setText("Pausar");
    } else if (estado == 0) {
        this->ui->btnTocar_Pausar->setText("Tocar");
        this->ui->actionTocar_Pausar->setText("Tocar");
    }
}

QString MainWindow::mudar_lblTempo( qint64 tempo ) {
    int     segundos = (tempo / 1000) % 60;
    int     minutos = (tempo / (1000 * 60)) % 60;
    int     horas = (tempo / (1000 * 60 * 60));

    QString formato = QString("%1:%2:%3")
            .arg(horas, 2, 10, QChar('0'))
            .arg(minutos, 2, 10, QChar('0'))
            .arg(segundos, 2, 10, QChar('0'));
    return (formato);
}
