#include "mainwindow.hpp"

void MainWindow::createTrayIcon()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(this, "MonaPlayer",
                            "Sistema não suporta bandeja do sistema.");
        return;
    }

    if (trayIcon) {
        trayIcon->hide();
        delete trayIcon;
        trayIcon = nullptr;
    }

    showAction = new QAction("&Mostrar MonaPlayer", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::showNormal);
    quitAction = new QAction("&Sair", this);
    connect(quitAction, &QAction::triggered, this, &MainWindow::on_actionSair_triggered);

    trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    trayIcon->setToolTip("MonaPlayer - Reprodutor de Música");

    connect(trayIcon, &QSystemTrayIcon::activated,
            this, &MainWindow::trayIconActivated);
    trayIcon->show();
}

void    MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (this->isVisible()) this->hide();
        else {
            this->showNormal();
            this->activateWindow();
            this->raise();
        }
        break;
    default:
        break;
    }
}

void    MainWindow::showNormal()
{
    this->show();
    this->activateWindow();
    this->raise();
}

// Override do evento de fecho
void    MainWindow::closeEvent(QCloseEvent *event)
{
    if (isQuitting || !trayIcon->isVisible()) {
        event->accept();
        return ;
    }

    static bool firstTime = true;
    if (firstTime) {
        trayIcon->showMessage("MonaPlayer",
                              "O programa continuará em execução na bandeja do sistema. "
                              "Para sair completamente, use o menu Arquivo > Sair.",
                              QSystemTrayIcon::Information, 3000);
        firstTime = false;
    }
    this->hide();
    event->ignore();
}
