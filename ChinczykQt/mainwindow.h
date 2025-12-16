#pragma once
#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "gra.h"
#include "boardscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void zbudujUI();
    void podlaczSygnaly();

private:
    Gra m_gra;
    BoardScene* m_scena = nullptr;

    QGraphicsView* m_view = nullptr;
    QPushButton* m_btnNowa = nullptr;
    QPushButton* m_btnRzut = nullptr;
    QComboBox* m_comboGracze = nullptr;
    QLabel* m_lblRzut = nullptr;
    QLabel* m_lblTura = nullptr;
};
