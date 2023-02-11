#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Pinyin2Hanzi/myPinyin.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString N = "吕布 吕不韦 南宫问天";
    QStringList Names = N.split(" ");
    //    qDebug() << Names;

    ui->comboBox->addItem("");
    ui->comboBox->addItems(Names);
    ui->comboBox->lineEdit()->setClearButtonEnabled(true);
    CreateCompleter(Names, ui->lineEdit);

//    QStringListModel *model = new QStringListModel(Names);
//    QCompleter *completer = new QCompleter(model, ui->comboBox->lineEdit());
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    completer->setFilterMode(Qt::MatchContains);
//    completer->setCompletionMode(QCompleter::PopupCompletion);
//    ui->comboBox->lineEdit()->setCompleter(completer);

    ui->comboBox->setMaxCount(ui->comboBox->count()); //这行代码可以防止按回车键自动往combobox里addItem

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 把所有人名按照拼音分类并存入map中
void MainWindow::PreparePinyinData(const QStringList &names)
{
    for (auto & name : names)
    {
        QString outFristPy,outFullPy;
        getComPingyinForStr(name, outFristPy, outFullPy);
        //        QString pinyin = GetPinyin(name);
        QString pinyin = outFullPy;
        //        qDebug() <<"FristPy:" << outFristPy << "FullPy:" << outFullPy;
        //        qDebug() <<"pinyin:" << pinyin;

        //        QString fist, last;
        //        myNameSplit(name, last, fist);     // 自动切分 [姓、名]
        //        last = getNamePingyin(last, true); // 获取 [姓] 的拼音
        //        fist = getNamePingyin(fist, false);// 获取 [名] 的拼音
        //        qDebug() << name + " : " + last + " " + fist << endl;

        pinyin2NameMap[pinyin.toStdString()].push_back(name);
    }
}

// 根据输入的拼音进行匹配并获取提示列表
QStringList MainWindow::GetMatchByPinyin(const QString &pinyin)
{
    QStringList result;

    if("" == pinyin.trimmed()){
        return QStringList();
    }

    for (const auto & iter : pinyin2NameMap){

        if (iter.first.find(pinyin.toStdString()) != std::string::npos){
            auto vec = iter.second;
            for(const auto & name : vec){
                result.append(name);
            }
        }
    }
    return result;
}

// 创建QCompleter并设置自动补全模型
void MainWindow::CreateCompleter(const QStringList &names, QLineEdit *lineEdit)
{
    PreparePinyinData(names);
    QStringListModel *model = new QStringListModel(names);
    QCompleter *completer = new QCompleter(model, lineEdit);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(completer);
    connect(lineEdit, &QLineEdit::textChanged, [this,completer,lineEdit,model](const QString &text)
    {
//        lineEdit->setFocus();
        QStringList matchList = GetMatchByPinyin(text);
//        qDebug() << text;
        qDebug() << "listmodel:" << matchList;
        model->setStringList(matchList);
//        completer->setModel(model);
//        completer->complete();
//        qDebug() << completer->model()->rowCount();
    });
}


