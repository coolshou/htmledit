#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextCodec>
#include <QAction>
#include <QMessageBox>


#include "version.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupFileActions();
    setupTextActions();
    setupHelpActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::load(const QString &f)
{
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    return activeHtmlEdit->load(f);
}

void MainWindow::fileNew()
{
    HtmlEdit *htmledit = new HtmlEdit();
    connect(htmledit, &HtmlEdit::fontStyle, this, &MainWindow::textStyle);
    connect(htmledit, &HtmlEdit::fontFamily, this, &MainWindow::textFamily);
    connect(htmledit, &HtmlEdit::fontSize, this, &MainWindow::textSize);
    connect(htmledit, &HtmlEdit::fontChanged, this, &MainWindow::fontChanged);
    connect(htmledit, &HtmlEdit::CheckState, this, &MainWindow::CheckState);
    connect(htmledit, &HtmlEdit::PasteState, this, &MainWindow::PasteState);
    connect(htmledit, &HtmlEdit::statusMesage, this, &MainWindow::statusMesage);
    /*
    connect(htmledit->widget(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(textEdit->document(), &QTextDocument::undoAvailable,
            actionUndo, &QAction::setEnabled);
    connect(textEdit->document(), &QTextDocument::redoAvailable,
            actionRedo, &QAction::setEnabled);
    */

    ui->mdiArea->addSubWindow(htmledit);
    htmledit->setWindowState(Qt::WindowMaximized);
//    htmledit->fileNew();
    htmledit->show();
}

void MainWindow::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList()
#if QT_CONFIG(texthtmlparser)
                                  << "text/html"
#endif
#if QT_CONFIG(textmarkdownreader)

                                  << "text/markdown"
#endif
                                  << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

void MainWindow::textFamily(const QString &f)
{
    comboFont->setCurrentFont(f);
}

void MainWindow::textSize(const QString &p)
{
    comboSize->setCurrentText(p);
}

void MainWindow::textStyle(int styleIndex)
{
    comboStyle->setCurrentIndex(styleIndex);
}

void MainWindow::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    ui->actionBold->setChecked(f.bold());
    ui->actionItalic->setChecked(f.italic());
    ui->actionUnderline->setChecked(f.underline());
}

void MainWindow::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actionTextColor->setIcon(pix);
}

void MainWindow::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        ui->actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        ui->actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        ui->actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        ui->actionAlignJustify->setChecked(true);
}

void MainWindow::CheckState(bool checked)
{
    ui->actionChecked->setChecked(checked);
}

void MainWindow::PasteState(bool enabled)
{
    ui->actionPaste->setEnabled(enabled);
}

void MainWindow::textBold()
{
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    int w = ui->actionBold->isChecked() ? QFont::Bold : QFont::Normal;
    activeHtmlEdit->textBold(w);

}

void MainWindow::textUnderline()
{
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textUnderline(ui->actionUnderline->isChecked());

}

void MainWindow::textItalic()
{
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textItalic(ui->actionItalic->isChecked());

}

void MainWindow::textAlign(QAction *a)
{
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textAlign(a);
}
void MainWindow::statusMesage(const QString &t)
{
    ui->statusbar->showMessage(t);

}
void MainWindow::setupFileActions()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));

}
void MainWindow::setupEditActions()
{

}
void MainWindow::setupTextActions()
{
    // Make sure the alignLeft  is always left of the alignRight
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &MainWindow::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(ui->actionAlignLeft);
        alignGroup->addAction(ui->actionAlignCenter);
        alignGroup->addAction(ui->actionAlignRight);
    } else {
        alignGroup->addAction(ui->actionAlignRight);
        alignGroup->addAction(ui->actionAlignCenter);
        alignGroup->addAction(ui->actionAlignLeft);
    }
    alignGroup->addAction(ui->actionAlignJustify);

//    tb->addActions(alignGroup->actions());
//    menu->addActions(alignGroup->actions());
//    tb->addAction(actionIndentMore);
//    tb->addAction(actionIndentLess);
//    menu->addAction(actionIndentMore);
//    menu->addAction(actionIndentLess);

//    menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    ui->actionTextColor->setIcon(pix);

//    addToolBarBreak(Qt::TopToolBarArea);
    addToolBarBreak();
    QToolBar *tb_fonts = addToolBar(tr("Fonts"));
    tb_fonts->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(tb_fonts);

    comboStyle = new QComboBox(tb_fonts);
    tb_fonts->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Task List (Unchecked)");
    comboStyle->addItem("Task List (Checked)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    comboStyle->addItem("Heading 1");
    comboStyle->addItem("Heading 2");
    comboStyle->addItem("Heading 3");
    comboStyle->addItem("Heading 4");
    comboStyle->addItem("Heading 5");
    comboStyle->addItem("Heading 6");

    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::setTextStyle);

    comboFont = new QFontComboBox(tb_fonts);
    tb_fonts->addWidget(comboFont);
    connect(comboFont, &QComboBox::textActivated, this, &MainWindow::setTextFamily);

    comboSize = new QComboBox(tb_fonts);
    comboSize->setObjectName("comboSize");
    tb_fonts->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, &QComboBox::textActivated, this, &MainWindow::setTextSize);
}

void MainWindow::setTextStyle(int styleIndex){
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textStyle(styleIndex);
}
void MainWindow::setTextFamily(const QString &f){
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textFamily(f);
}
void MainWindow::setTextSize(const QString &p){
    activeHtmlEdit = (HtmlEdit*)ui->mdiArea->activeSubWindow();
    activeHtmlEdit->textSize(p);
}

void MainWindow::setupHelpActions()
{
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onActionAboutTriggered()));

}


void MainWindow::on_actionNext_triggered()
{
    ui->mdiArea->activateNextSubWindow();
}


void MainWindow::on_actionPrevious_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}


void MainWindow::on_actionClose_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}


void MainWindow::on_actionClose_all_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}


void MainWindow::on_actionTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}


void MainWindow::on_actionCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::onActionAboutTriggered()
{
    QMessageBox::about(this, tr("About"), tr("simple html WYSWYG editor\n version: " HTMLEDIT_VER));

}

