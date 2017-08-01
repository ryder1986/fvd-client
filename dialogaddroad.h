#ifndef DIALOGADDROAD_H
#define DIALOGADDROAD_H

#include <QDialog>

namespace Ui {
class DialogAddRoad;
}

class DialogAddRoad : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddRoad(QWidget *parent = 0);
    ~DialogAddRoad();

private slots:


    void on_buttonBox_accepted();
  signals:
    void ok_clicked(QString road_name);

private:
    Ui::DialogAddRoad *ui;
};

#endif // DIALOGADDROAD_H
