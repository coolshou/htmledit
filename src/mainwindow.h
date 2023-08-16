#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "htmlsubwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QPrinter;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;
    bool load(const QString &f);
public slots:
    void fileNew();

private slots:
    void about();
    void fileOpen();
    /*
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);
    void setChecked(bool checked);
    void indent();
    void unindent();

    //void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();

    void printPreview(QPrinter *);
*/
private:
    Ui::MainWindow *ui;
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setupHelpActions();
};
#endif // MAINWINDOW_H
