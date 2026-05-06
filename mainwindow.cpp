#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGame();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameUpdate);
    timer->start(30);  // 每30ms刷新一次
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    // 初始化玩家
    player.x = 200;
    player.y = 200;
    player.radius = 20;
    player.color = Qt::blue;

    // 初始化食物
    foods.clear();
    for(int i=0;i<50;i++) spawnFood();

    score = 0;
}

void MainWindow::spawnFood()
{
    Ball f;
    f.x = QRandomGenerator::global()->bounded(400);
    f.y = QRandomGenerator::global()->bounded(400);
    f.radius = 5 + QRandomGenerator::global()->bounded(10);
    f.color = Qt::red;
    foods.push_back(f);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 绘制玩家
    painter.setBrush(player.color);
    painter.drawEllipse(player.x - player.radius, player.y - player.radius,
                        player.radius*2, player.radius*2);

    // 绘制食物
    for(const Ball &f : foods){
        painter.setBrush(f.color);
        painter.drawEllipse(f.x - f.radius, f.y - f.radius,
                            f.radius*2, f.radius*2);
    }

    // 显示分数
    painter.setPen(Qt::black);
    painter.drawText(10,20, QString("Score: %1").arg(score));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int step = 5;
    if(event->key() == Qt::Key_Up) player.y -= step;
    else if(event->key() == Qt::Key_Down) player.y += step;
    else if(event->key() == Qt::Key_Left) player.x -= step;
    else if(event->key() == Qt::Key_Right) player.x += step;
}

void MainWindow::gameUpdate()
{
    checkCollision();
    update(); // 重绘界面
}

void MainWindow::checkCollision()
{
    for(int i = foods.size()-1; i >= 0; --i){
        Ball &f = foods[i];
        int dx = player.x - f.x;
        int dy = player.y - f.y;
        int distance = sqrt(dx*dx + dy*dy);
        if(distance < player.radius + f.radius){
            player.radius += f.radius/4; // 吃掉食物增大
            score += 1;
            foods.remove(i);
            spawnFood(); // 生成新食物
        }
    }
}
