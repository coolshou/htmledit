#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QComboBox>
#include <QFontComboBox>
#include <QPixmap>

#include "htmledit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QPrinter;
class QComboBox;
class QFontComboBox;
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
    void setTextStyle(int styleIndex);
    void setTextFamily(const QString &f);
    void setTextSize(const QString &p);
    void statusMesage(const QString &t);

private slots:
    void fileOpen();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);
    void CheckState(bool checked);
    void PasteState(bool enabled);
    void textBold();
    void textUnderline();
    void textItalic();
    void textAlign(QAction *a);

    /*
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintP#include <QFontComboBox>df();

    void textColor();

    void setChecked(bool checked);
    void indent();
    void unindent();

    //void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();

    void printPreview(QPrinter *);
*/
    void on_actionNext_triggered();
    void on_actionPrevious_triggered();
    void on_actionClose_triggered();
    void on_actionClose_all_triggered();
    void on_actionTile_triggered();
    void on_actionCascade_triggered();
    void on_actionSave_triggered();
    void onActionAboutTriggered();

private:
    Ui::MainWindow *ui;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    HtmlEdit *activeHtmlEdit;
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setupHelpActions();

};
#endif // MAINWINDOW_H
