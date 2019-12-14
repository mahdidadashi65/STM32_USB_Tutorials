ifndef DIALOGSTATUS_H
#define DIALOGSTATUS_H

#include <QDialog>

namespace Ui {
class DialogStatus;
}

class DialogStatus : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStatus(QWidget *parent = 0);
    ~DialogStatus();

    int getData(uint8_t *Data);

private:
    Ui::DialogStatus *ui;
};

#endif // DIALOGSTATUS_H
