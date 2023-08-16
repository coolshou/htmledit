#ifndef HTMLSUBWIN_H
#define HTMLSUBWIN_H

#include <QMdiSubWindow>
#include "htmledit.h"

class HtmlSubWin : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit HtmlSubWin(QWidget *parent = nullptr);
    ~HtmlSubWin()override;

private:
    //Ui::HtmlSubWin *ui;
    HtmlEdit *htmledit;
};

#endif // HTMLSUBWIN_H
