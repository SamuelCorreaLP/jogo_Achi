#include "Achi.h"
#include "ui_Achi.h"

#include <QMessageBox>
#include <QSignalMapper>

#include <QDebug>

// TP2 de Linguagem de Programação
// Professor: Andrei Rimsa
// Aluno: Samuel Correa Lucas Pereira

Achi::Achi(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Achi) {

    ui->setupUi(this);

    QObject::connect(ui->actionNovo, SIGNAL(triggered(bool)), this, SLOT(reset()));
    QObject::connect(ui->actionSair, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject::connect(ui->actionSobre, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    //QObject::connect(ui->statusbar, SIGNAL(), this, SLOT());

    // Load the pieces.
    QSignalMapper* map = new QSignalMapper(this);
    for (int id = 0; id < 9; ++id) {
        int r = id / 3;
        int c = id % 3;

        Hole* hole = this->findChild<Hole*>(QString("hole%1%2").arg(r).arg(c));
        Q_ASSERT(hole != nullptr);

        m_holes[id] = hole;
        map->setMapping(hole, id);
        QObject::connect(hole, SIGNAL(clicked()), map, SLOT(map()));
    }
    QObject::connect(map, SIGNAL(mapped(int)), this, SLOT(play(int)));

    statusBar()->showMessage("Fase de posição: vez player Red");
    m_turn = 0;
    m_idAnterior = 0;

    // Compact the layout of the widgets.
    this->adjustSize();

    // Set a fixed window size.
    this->setFixedSize(this->size());
}

Achi::~Achi() {
    delete ui;
}

void Achi::play(int index) {
    Hole* hole = m_holes[index];
    Q_ASSERT(hole != nullptr);
    if(m_turn < 6){                                  //parte 1 do codigo
        if(m_turn % 2 == 0) {                        // vez do red
            if(hole->state() == Hole::EmptyState){
                //qDebug() << QString("hole: %1(%2, %3)Turn: %4").arg(index).arg(hole->row()).arg(hole->col()).arg(m_turn);
                hole->setState(Hole::RedState);
                m_turn++;
                statusBar()->showMessage("Fase de posição: vez player Blue");
            }
        } else {                                    //vez do blue
            if(hole->state() == Hole::EmptyState) {
                //qDebug() << QString("hole: %1(%2, %3)Turn: %4").arg(index).arg(hole->row()).arg(hole->col()).arg(m_turn);
                hole->setState(Hole::BlueState);
                m_turn++;
                statusBar()->showMessage("Fase de posição: vez player Red");
            }
        }
    } else {                                          //Segunda parte do jogo
        if(m_turn % 2 == 0) {                         //Vez do red
            if(hole->state() == Hole::RedState){      //colocar como selectable
                m_idAnterior = index;
                selectable2empty();
                empty2selectable(index);
            } else if(hole->state() == Hole::SelectableState) {    //trocar esfera
                //qDebug() << QString("hole: %1(%2, %3)Turn: %4").arg(index).arg(hole->row()).arg(hole->col()).arg(m_turn);
                hole->setState(Hole::RedState);
                m_holes[m_idAnterior]->setState(Hole::EmptyState);
                selectable2empty();
                statusBar()->showMessage("Fase de movimento: vez player Blue");
                m_turn++;
            }
        } else {                                     //Vez do blue
            if(hole->state() == Hole::BlueState){    //colocar como selectable
                m_idAnterior = index;
                selectable2empty();
                empty2selectable(index);
            } else if(hole->state() == Hole::SelectableState) {    //trocar esfera
                //qDebug() << QString("hole: %1(%2, %3)Turn: %4").arg(index).arg(hole->row()).arg(hole->col()).arg(m_turn);
                hole->setState(Hole::BlueState);
                m_holes[m_idAnterior]->setState(Hole::EmptyState);
                selectable2empty();
                statusBar()->showMessage("Fase de movimento: vez player Red");
                m_turn++;
            }
        }
    }
    if(m_turn == 6) {
        statusBar()->showMessage("Fase de movimento: vez player Red");
    }
    winCondition();
}

void Achi::winCondition() {
    if(m_holes[0]->state() == Hole::BlueState && m_holes[1]->state() == Hole::BlueState &&  //vitoria blue
            m_holes[2]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[3]->state() == Hole::BlueState && m_holes[6]->state() == Hole::BlueState &&
                   m_holes[8]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[7]->state() == Hole::BlueState && m_holes[4]->state() == Hole::BlueState &&
               m_holes[5]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    }else if (m_holes[0]->state() == Hole::BlueState && m_holes[3]->state() == Hole::BlueState &&
              m_holes[7]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[1]->state() == Hole::BlueState && m_holes[6]->state() == Hole::BlueState &&
               m_holes[4]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[2]->state() == Hole::BlueState && m_holes[8]->state() == Hole::BlueState &&
               m_holes[5]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[0]->state() == Hole::BlueState && m_holes[6]->state() == Hole::BlueState &&
               m_holes[5]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if (m_holes[7]->state() == Hole::BlueState && m_holes[6]->state() == Hole::BlueState &&
               m_holes[2]->state() == Hole::BlueState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador blue venceu."));
        reset();
    } else if(m_holes[0]->state() == Hole::RedState && m_holes[1]->state() == Hole::RedState &&  //vitoria red
            m_holes[2]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[3]->state() == Hole::RedState && m_holes[6]->state() == Hole::RedState &&
                   m_holes[8]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[7]->state() == Hole::RedState && m_holes[4]->state() == Hole::RedState &&
               m_holes[5]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    }else if (m_holes[0]->state() == Hole::RedState && m_holes[3]->state() == Hole::RedState &&
              m_holes[7]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[1]->state() == Hole::RedState && m_holes[6]->state() == Hole::RedState &&
               m_holes[4]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[2]->state() == Hole::RedState && m_holes[8]->state() == Hole::RedState &&
               m_holes[5]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[0]->state() == Hole::RedState && m_holes[6]->state() == Hole::RedState &&
               m_holes[5]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    } else if (m_holes[7]->state() == Hole::RedState && m_holes[6]->state() == Hole::RedState &&
               m_holes[2]->state() == Hole::RedState) {
        QMessageBox::information(this, tr("Vitoria"), tr("Parabens, jogador red venceu."));
        reset();
    }
}

void Achi::selectable2empty() {
    Hole* hole;
    for(int id = 0; id < 9; id++) {
        hole = m_holes[id];
        Q_ASSERT(hole != nullptr);

        if(hole->state() == Hole::SelectableState){
            hole->setState(Hole::EmptyState);
        }
    }
}

void Achi::empty2selectable(int id) {
    switch(id) {
    case 0:
        if(m_holes[1]->state() == Hole::EmptyState) {
            m_holes[1]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        if(m_holes[3]->state() == Hole::EmptyState) {
            m_holes[3]->setState(Hole::SelectableState);
        }
        break;
    case 1:
        if(m_holes[0]->state() == Hole::EmptyState) {
            m_holes[0]->setState(Hole::SelectableState);
        }
        if(m_holes[2]->state() == Hole::EmptyState) {
            m_holes[2]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        break;
    case 2:
        if(m_holes[1]->state() == Hole::EmptyState) {
            m_holes[1]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        if(m_holes[8]->state() == Hole::EmptyState) {
            m_holes[8]->setState(Hole::SelectableState);
        }
        break;
    case 3:
        if(m_holes[0]->state() == Hole::EmptyState) {
            m_holes[0]->setState(Hole::SelectableState);
        }
        if(m_holes[7]->state() == Hole::EmptyState) {
            m_holes[7]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        break;
    case 4:
        if(m_holes[7]->state() == Hole::EmptyState) {
            m_holes[7]->setState(Hole::SelectableState);
        }
        if(m_holes[5]->state() == Hole::EmptyState) {
            m_holes[5]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        break;
    case 5:
        if(m_holes[4]->state() == Hole::EmptyState) {
            m_holes[4]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        if(m_holes[8]->state() == Hole::EmptyState) {
            m_holes[8]->setState(Hole::SelectableState);
        }
        break;
    case 6:
        if(m_holes[0]->state() == Hole::EmptyState) {
            m_holes[0]->setState(Hole::SelectableState);
        }
        if(m_holes[1]->state() == Hole::EmptyState) {
            m_holes[1]->setState(Hole::SelectableState);
        }
        if(m_holes[2]->state() == Hole::EmptyState) {
            m_holes[2]->setState(Hole::SelectableState);
        }
        if(m_holes[3]->state() == Hole::EmptyState) {
            m_holes[3]->setState(Hole::SelectableState);
        }
        if(m_holes[8]->state() == Hole::EmptyState) {
            m_holes[8]->setState(Hole::SelectableState);
        }
        if(m_holes[7]->state() == Hole::EmptyState) {
            m_holes[7]->setState(Hole::SelectableState);
        }
        if(m_holes[4]->state() == Hole::EmptyState) {
            m_holes[4]->setState(Hole::SelectableState);
        }
        if(m_holes[5]->state() == Hole::EmptyState) {
            m_holes[5]->setState(Hole::SelectableState);
        }
        break;
    case 7:
        if(m_holes[3]->state() == Hole::EmptyState) {
            m_holes[3]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        if(m_holes[4]->state() == Hole::EmptyState) {
            m_holes[4]->setState(Hole::SelectableState);
        }
        break;
    case 8:
        if(m_holes[2]->state() == Hole::EmptyState) {
            m_holes[2]->setState(Hole::SelectableState);
        }
        if(m_holes[5]->state() == Hole::EmptyState) {
            m_holes[5]->setState(Hole::SelectableState);
        }
        if(m_holes[6]->state() == Hole::EmptyState) {
            m_holes[6]->setState(Hole::SelectableState);
        }
        break;
    default:
        break;
    }
}

void Achi::showAbout() {
    QMessageBox::information(this, tr("Sobre"), tr("Achi\n\nSamuel Correa Lucas Pereira - samuelcorrea@hotmail.com"));
}

void Achi::reset() {
    m_turn = 0;
    statusBar()->showMessage("Fase de posição: vez player Red");
    for (int id = 0; id < 9; ++id) {
        Hole* hole = m_holes[id];
        Q_ASSERT(hole != nullptr);

        m_holes[id]->reset();
    }
}
