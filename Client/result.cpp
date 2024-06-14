#include "result.h"
#include "ui_result.h"
#include "config.h"
#include <QPixmap>

Result::Result(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Result)
{
    ui->setupUi(this);

    setWindowTitle(GAME_NAME);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    QPixmap pixmap(RESULT_PATH);
    resize(pixmap.size());
    setMask(pixmap.mask());

    connect(ui->backButton, &QPushButton::clicked, this, [this](){
        this->close();
    });
}

Result::~Result()
{
    delete ui;
}
