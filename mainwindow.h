#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <map>
#include <vector>
#include <string>
#include <QCompleter>
#include <QStringListModel>
#include <QLineEdit>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void PreparePinyinData(const QStringList &names);
    QStringList GetMatchByPinyin(const QString &pinyin);
    void CreateCompleter(const QStringList &names, QLineEdit *lineEdit);
private:
    Ui::MainWindow *ui;

    std::map<std::string, std::vector<QString>> pinyin2NameMap;
//    QStringList Names;
};
#endif // MAINWINDOW_H
