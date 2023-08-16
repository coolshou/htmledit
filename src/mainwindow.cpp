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
    setupHelpActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::load(const QString &f)
{
//    if (!QFile::exists(f))
//        return false;
//    QFile file(f);
//    if (!file.open(QFile::ReadOnly))
//        return false;

//    QByteArray data = file.readAll();
//    QTextCodec *codec = Qt::codecForHtml(data);
//    QString str = codec->toUnicode(data);
//    if (Qt::mightBeRichText(str)) {
//        QUrl baseUrl = (f.front() == QLatin1Char(':') ? QUrl(f) : QUrl::fromLocalFile(f)).adjusted(QUrl::RemoveFilename);
//        textEdit->document()->setBaseUrl(baseUrl);
//        textEdit->setHtml(str);
//    } else {
//#if QT_CONFIG(textmarkdownreader)
//        QMimeDatabase db;
//        if (db.mimeTypeForFileNameAndData(f, data).name() == QLatin1String("text/markdown"))
//            textEdit->setMarkdown(QString::fromUtf8(data));
//        else
//#endif
//            textEdit->setPlainText(QString::fromUtf8(data));
//    }

//    setCurrentFileName(f);
    //    return true;
}

void MainWindow::fileNew()
{
    /*if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName(QString());
    }*/
    qDebug() << "fileNew" << Qt::endl;

    HtmlSubWin *hsubwin = new HtmlSubWin();
//    qDebug() << "hsubwin" << Qt::endl;
//    hsubwin->showMaximized();
//    qDebug() << "showMaximized" << Qt::endl;
    ui->mdiArea->addSubWindow(hsubwin)->setWindowState(Qt::WindowMaximized);

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

void MainWindow::setupFileActions()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));

}
void MainWindow::setupEditActions()
{

}
void MainWindow::setupTextActions(){

}
void MainWindow::setupHelpActions()
{
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("simple html WYSWYG editor\n version: " HTMLEDIT_VER));
}
