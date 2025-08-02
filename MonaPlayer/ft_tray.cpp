#include "mainwindow.hpp"

void MainWindow::createTrayIcon()
{
    if (trayIcon) return; // Já existe, não criar novamente

    // Verificar suporte básico
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(this, "MonaPlayer",
                            "Sistema não suporta bandeja do sistema.");
        return;
    }

    // Configurar por plataforma
    setupPlatformSpecificTray();

    // Criar ações do menu
    showAction = new QAction("&Mostrar MonaPlayer", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::showNormal);

    quitAction = new QAction("&Sair", this);
    connect(quitAction, &QAction::triggered, this, &MainWindow::on_actionSair_triggered);

    // Criar menu da bandeja
    trayMenu = new QMenu(this);
    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    // Criar ícone da bandeja
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    trayIcon->setToolTip("MonaPlayer - Mona nga mu ngoma");

    // Conectar duplo clique
    connect(trayIcon, &QSystemTrayIcon::activated,
            this, &MainWindow::trayIconActivated);

    // Mostrar na bandeja
    trayIcon->show();
}

void    MainWindow::setupPlatformSpecificTray()
{
#ifdef Q_OS_LINUX
    // Tentar forçar área de notificações tradicional primeiro
    qputenv("QT_QPA_PLATFORMTHEME", "");

    // Verificar se existe área de notificações tradicional
    bool hasTraditionalTray = false;

    // Verificar via D-Bus se existe um sistema de bandeja tradicional
    QDBusInterface interface("org.kde.StatusNotifierWatcher",
                             "/StatusNotifierWatcher",
                             "org.kde.StatusNotifierWatcher");

    if (interface.isValid())
        hasTraditionalTray = true;

    if (!hasTraditionalTray)
        qputenv("QT_QPA_PLATFORMTHEME", "gtk3"); // Se não tem área tradicional, usar AppIndicator
#endif
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
