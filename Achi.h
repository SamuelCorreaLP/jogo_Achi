#ifndef ACHI_H
#define ACHI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Achi;
}
QT_END_NAMESPACE

class Hole;

class Achi : public QMainWindow {
    Q_OBJECT

public:
    Achi(QWidget *parent = nullptr);
    virtual ~Achi();

private:
    void empty2selectable(int id);
    void selectable2empty();
    void winCondition();

    Ui::Achi *ui;
    Hole* m_holes[9];
    int m_turn;
    int m_idAnterior;

private slots:
    void play(int id);
    void reset();
    void showAbout();

};

#endif // ACHI_H
