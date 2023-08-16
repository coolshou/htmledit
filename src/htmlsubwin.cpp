#include "htmlsubwin.h"

HtmlSubWin::HtmlSubWin(QWidget *parent) :
    QMdiSubWindow(parent)
{
    htmledit = new HtmlEdit();
    setWidget(htmledit);
    setAttribute(Qt::WA_DeleteOnClose);
//    setWindowIcon();
    setWindowTitle("New");
}

HtmlSubWin::~HtmlSubWin()
{
    //delete ui;
}
