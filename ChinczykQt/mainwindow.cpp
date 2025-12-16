#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    zbudujUI();
    podlaczSygnaly();

    m_gra.nowaGra(4);
}

void MainWindow::zbudujUI()
{
    auto* central = new QWidget(this);
    setCentralWidget(central);

    m_view = new QGraphicsView(this);
    m_view->setRenderHint(QPainter::Antialiasing, true);

    m_scena = new BoardScene(&m_gra, this);
    m_view->setScene(m_scena);

    m_btnNowa = new QPushButton("Nowa gra", this);
    m_btnRzut = new QPushButton("Rzut kostka", this);

    m_comboGracze = new QComboBox(this);
    m_comboGracze->addItem("2 graczy", 2);
    m_comboGracze->addItem("3 graczy", 3);
    m_comboGracze->addItem("4 graczy", 4);
    m_comboGracze->setCurrentIndex(2);

    m_lblRzut = new QLabel("Rzut: -", this);
    m_lblTura = new QLabel("Tura: -", this);

    auto* gora = new QHBoxLayout();
    gora->addWidget(m_comboGracze);
    gora->addWidget(m_btnNowa);
    gora->addSpacing(20);
    gora->addWidget(m_btnRzut);
    gora->addSpacing(20);
    gora->addWidget(m_lblTura);
    gora->addWidget(m_lblRzut);
    gora->addStretch(1);

    auto* layout = new QVBoxLayout(central);
    layout->addLayout(gora);
    layout->addWidget(m_view);

    resize(900, 900);
    setWindowTitle("Chinczyk (Ludo) - Qt");
    statusBar()->showMessage("Gotowe.");
}

void MainWindow::podlaczSygnaly()
{
    connect(m_btnNowa, &QPushButton::clicked, this, [this](){

        auto czyGraTrwa = [this]() -> bool
        {
            if (m_gra.gracze().isEmpty()) return false;
            if (m_gra.czyRzucono() || m_gra.ostatniRzut() != 0) return true;

            for (const auto& g : m_gra.gracze())
                for (const auto& p : g.pionki())
                    if (!p.wBazie())
                        return true;

            return false;
        };

        if (czyGraTrwa())
        {
            auto odp = QMessageBox::question(
                this,
                "Nowa gra",
                "Zakoncz obecna gre i rozpocznij nowa?",
                QMessageBox::Yes | QMessageBox::No
                );

            if (odp == QMessageBox::No)
                return;
        }

        int n = m_comboGracze->currentData().toInt();

        if (m_scena)
            m_scena->resetujTlo();  // wywal stare pionki ze sceny ZANIM powstana nowe

        m_gra.nowaGra(n);
    });

    connect(m_btnRzut, &QPushButton::clicked, this, [this](){
        m_gra.rzutKostka();
    });

    connect(&m_gra, &Gra::stanZmieniony, this, [this](){
        m_lblTura->setText("Tura: " + kolorNaTekst(m_gra.aktualnyGracz().kolor()));

        if (m_gra.czyRzucono())
            m_lblRzut->setText("Rzut: " + QString::number(m_gra.ostatniRzut()));
        else
            m_lblRzut->setText("Rzut: -");

        // zeby nie dalo sie rzucic drugi raz przed ruchem / w trakcie "brak ruchu"
        m_btnRzut->setEnabled(!m_gra.czyRzucono());

        m_scena->odswiez();
    });

    connect(&m_gra, &Gra::komunikat, this, [this](const QString& t){
        statusBar()->showMessage(t, 5000);
    });

    connect(&m_gra, &Gra::koniecGry, this, [this](const QString& zwyciezca){

        QMessageBox box(this);
        box.setIcon(QMessageBox::Information);
        box.setWindowTitle("Koniec gry");
        box.setText("Koniec gry wygral: " + zwyciezca);

        // tylko te przyciski
        auto* btnNowa = box.addButton("Rozpocznij nowa gre", QMessageBox::AcceptRole);
        QPushButton* btnKont = nullptr;

        if (m_gra.moznaKontynuowacPoWygranej())
            btnKont = box.addButton("Kontynuuj", QMessageBox::RejectRole);

        // bez X i bez zamykania Esc
        box.setWindowFlags(box.windowFlags() & ~Qt::WindowCloseButtonHint);
        box.setDefaultButton(btnNowa);
        box.setEscapeButton(btnNowa);

        box.exec();

        if (box.clickedButton() == btnNowa)
        {
            int n = m_comboGracze->currentData().toInt();
            m_scena->resetujTlo();
            m_gra.nowaGra(n);
            return;
        }

        if (btnKont && box.clickedButton() == btnKont)
            m_gra.kontynuujPoWygranej();
    });

}
