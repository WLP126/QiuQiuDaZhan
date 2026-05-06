#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Ball {
    int x;
    int y;
    int radius;
    QColor color;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;   // 绘图
    void keyPressEvent(QKeyEvent *event) override;  // 键盘控制

private slots:
    void gameUpdate();  // 游戏循环

private:
    Ui::MainWindow *ui;

    Ball player;              // 玩家球
    QVector<Ball> foods;      // 食物球列表
    int score;                // 玩家分数
    QTimer *timer;            // 游戏刷新定时器

    void initGame();          // 初始化游戏
    void spawnFood();         // 生成食物
    void checkCollision();    // 检测碰撞
};

#endif // MAINWINDOW_H
