/* Class: Course
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 *
 * Class that opens the mainwindow and handles the whole functionality of the
 * game Tetris.
 *
 * This program goes through the information of the tetromino in loops.
 * Because tetromino's blocks are in a vector, the program has to check every
 * block before doing anything.
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <tetromino.hh>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Timer is used to count the actual time.
    QTimer* timer_;

private slots:
    // Handles the updating of the timer_.
    void tic();

    // Sets the game in motion by handling the buttons and tempo_.
    void on_startPushButton_clicked();

    // Moves the tetromino to the left immediately, if possible.
    void on_leftPushButton_clicked();

    // Moves the tetromino to the right immediately, if possible.
    void on_rightPushButton_clicked();

    // Drops the tetromino as down as possible.
    void on_downPushButton_clicked();

    // Game starts all over again and scene_ is cleared.
    void on_restartPushButton_clicked();

private:
    Ui::MainWindow *ui;
    // Scene is the game board.
    QGraphicsScene* scene_;
    // Tetrominos move along with this pase.
    QTimer tempo_;
    // Is used with the timer_
    QTime* time_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // How many blocks every tetromino contain.
    const int BLOCKS = 4;

    // All the colors that are used in tetrominos. Every shape has their own
    // color.
    std::vector<QBrush> colors{QBrush(QColor(255, 219, 40)),   // yellow
                               QBrush(QColor(157, 197, 92)),    // lightgreen
                               QBrush(QColor(245, 135, 101)),   // reddish
                               QBrush(QColor(44, 190, 177)),    // blue
                               QBrush(QColor(255, 159, 15)),    // orange
                               QBrush(QColor(95, 149, 28)),     // green
                               QBrush(QColor(255, 244, 193))};  // white

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HERO,
                         BLUE_RICKY,
                         ORANGE_RICKY,
                         SMASHBOY,
                         RHODE_ISLAND_Z,
                         TEEWEE,
                         CLEVELAND_Z,
                         NUMBER_OF_TETROMINOS};

    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // Stores the current tetromino's blocks into thi vector.
    std::vector<QGraphicsRectItem*> current_tetromino_;

    // Stores the coordinates of all current blocks.
    std::vector<qreal> current_x_;
    std::vector<qreal> current_y_;

    // Holds information of the places that are occupied with already placed
    // tetromino blocks. In to these coordinates tetrominos cannot go to.
    std::vector<std::vector<double>> occupied_places_;

    // Random tetromino is placed into it's first position if it's possible..
    void initialize_tetromino();

    // Moves the tetromino downward at every time tempo_ "tics".
    void move();

    // Clears all the vectors that hold current information of a tetromino.
    void new_tetromino();

    // Takes care the game ends and everything stops.
    void end_game();

    // Returns true value if the tetromino can move.
    bool can_move();
};

#endif // MAINWINDOW_HH
