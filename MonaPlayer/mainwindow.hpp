#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QUrl>

#include <QSystemTrayIcon>
#include <QStyle>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>

#include <iostream>
#include <string>

#include "ui_mainwindow.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // void funcs
    void    tocar_pausar( void );
    void    escolher_musica( void );
    void    updateSliderVolume( int volume );
    void    updateSliderTempoPos( qint64 posicao );
    void    updateSliderTempoDur( qint64 duracao );

    // QString funcs
    QString mudar_lblTempo( qint64 tempo );

    // musicinfo funcs
    void    printMsg( const string & msg );
    bool    setArquivo( void );
    void    setVolume( int valor );
    void    setPosicao( int valor );
    int     tocar_pausarMusica( void );

protected:
    void    closeEvent( QCloseEvent *event ) override;

private slots:
    // bandeja do sistema funcs
    void trayIconActivated( QSystemTrayIcon::ActivationReason reason );
    void showNormal( void );

    void on_sliderVolume_valueChanged(int value);

    void on_btnEscolher_Musica_clicked();

    void on_btnTocar_Pausar_clicked();

    void on_actionTocar_Pausar_triggered();

    void on_sliderTempo_sliderMoved(int position);

    void on_sliderTempo_sliderReleased();

    void on_actionAbrir_arquivo_triggered();

    void on_actionAumentar_Volume_10_triggered();

    void on_actionDiminuir_Volume_10_triggered();

    void on_sliderTempo_sliderPressed();

    void on_actionSobre_triggered();

    void on_actionCreditos_triggered();

    void on_actionSair_triggered();

private:
    Ui::MainWindow  *ui;

    // bandeja do sistema var(s)
    QSystemTrayIcon *trayIcon;
    QMenu           *trayMenu;
    QAction         *showAction;
    QAction         *quitAction;
    void            createTrayIcon();

    bool            isQuitting;
    bool            sliderTempoMovendo;

    QString         arquivo;
    QMediaPlayer    *player;
};

#endif // MAINWINDOW_HPP
