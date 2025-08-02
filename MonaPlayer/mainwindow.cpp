#include "mainwindow.hpp"

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , trayIcon(nullptr)
    , trayMenu(nullptr)
    , showAction(nullptr)
    , quitAction(nullptr)
{
    ui->setupUi(this);

    this->sliderTempoMovendo = false;
    this->isQuitting = false;
    this->arquivo = "";

    this->player = new QMediaPlayer(this);
    this->player->setVolume(44);

    connect(player, &QMediaPlayer::volumeChanged, this, &MainWindow::updateSliderVolume);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSliderTempoPos);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateSliderTempoDur);

    // Erro ao carregar o arquivo (arquivo corrompido, formato não suportado, etc.)
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            [=](QMediaPlayer::Error error) {
        (void)error;
        QMessageBox::warning(this, "Erro", "Não foi possível reproduzir o arquivo selecionado.");
    });

    // Criar System Tray
    this->createTrayIcon();
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
    QMessageBox::about(this, "Sobre o MonaPlayer",
        "🎵 MonaPlayer v1.0 🎵\n\n"
        "Um reprodutor de música simples e elegante, desenvolvido com tecnologia Qt.\n"
        "O MonaPlayer permite reproduzir os teus ficheiros de áudio favoritos com "
        "uma interface limpa e intuitiva.\n\n"
        "Funcionalidades:\n"
        "• Reprodução de ficheiros MP3, WAV, FLAC e outros\n"
        "• Controlo de volume e posição\n"
        "• Interface amigável e responsiva\n\n"
        "Criado por: Eliandro Sérgio\n"
        "Angola 🇦🇴 | 2025\n\n"
        "\"Música é a linguagem universal da alma\"");
}

void MainWindow::on_actionCreditos_triggered()
{
    QMessageBox::about(this, "Créditos",
        "🏆 CRÉDITOS 🏆\n\n"
        "👨‍💻 Desenvolvedor:\n"
        "Eliandro Sérgio\n"
        "GitHub: github.com/eliandrosergio\n\n"
        "🔧 Tecnologias Utilizadas:\n"
        "• Qt Framework (Interface e Multimédia)\n"
        "• C++ (Linguagem de Programação)\n"
        "• Qt Creator (Ambiente de Desenvolvimento)\n\n"
        "📚 Bibliotecas:\n"
        "• Qt Multimedia (Reprodução de áudio)\n"
        "• Qt Widgets (Interface gráfica)\n\n"
        "🙏 Agradecimentos especiais:\n"
        "• Comunidade Qt pela excelente documentação\n"
        "• Comunidade C++ pelo suporte contínuo\n\n"
        "Feito com ❤️ em Angola");
}

void MainWindow::on_actionSair_triggered()
{
    QMessageBox::StandardButton resposta = QMessageBox::question(
        this,
        "Sair",
        "Tens a certeza que queres sair do MonaPlayer?",
        QMessageBox::Yes | QMessageBox::No
    );
    if (resposta == QMessageBox::Yes) {
        isQuitting = true;
        this->close();
        QApplication::quit();
    }
}
