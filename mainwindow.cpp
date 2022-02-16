#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // This is the graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0);
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng);

    // Set timer for continuous movement.
    tempo_.setSingleShot(false);
    connect(&tempo_, &QTimer::timeout, this, &MainWindow::move);

    // Set time values to start.
    time_ = new QTime( 0, 0, 0 );
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(tic()));

    ui->rightPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);
    ui->restartPushButton->setDisabled(true);

    ui->gameOverText->hide();
    ui->restartPushButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    if ( time_ != nullptr ) {
        delete time_;
        scene_->clear();
    }
}

void MainWindow::on_startPushButton_clicked()
{
    if ( !timer_->isActive() )
        timer_->start(1000);
    tempo_.start(500);

    ui->startPushButton->setDisabled(true);
    ui->startPushButton->hide();

    ui->rightPushButton->setDisabled(false);
    ui->leftPushButton->setDisabled(false);
    ui->downPushButton->setDisabled(false);

    initialize_tetromino();
}

void MainWindow::initialize_tetromino()
{
    // Defines the outline of the block.
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    // Chooses the tetromino randomly.
    int random = distr(randomEng);
    Tetromino tetromino;
    std::vector<int> t = tetromino.choose_tetromino(random);

    // Following loop checks if the tetromino can be initialized.
    int i = 0;
    while ( i < BLOCKS*2 ) {
        // Current position of the tetromino.
        qreal pos_x = t.at(i);
        qreal pos_y = t.at(i+1);

        std::vector<double> current_coordinates{pos_x, pos_y};
        for ( auto coordinates : occupied_places_ ) {
            if ( coordinates == current_coordinates ) {
                end_game();   // ENDS THE GAME.
                return;
            }
        }
        current_x_.push_back(pos_x);
        current_y_.push_back(pos_y);
        i += 2;
    }

    // Adds the tetromino into the scene_.
    i = 0;
    while ( i < BLOCKS*2 ) {
        current_tetromino_.push_back(scene_->addRect(t.at(i), t.at(i+1),
                                                     SQUARE_SIDE, SQUARE_SIDE,
                                                     blackPen, colors.at(random)));
        i += 2;
    }
}

void MainWindow::move()
{
    int i = 0;
    if ( can_move() ) {
        while ( i < BLOCKS ) {
            current_y_.at(i) += SQUARE_SIDE;
            current_tetromino_.at(i)->moveBy(0, static_cast<qreal>(SQUARE_SIDE));
            i++;
        }
    } else {
        i = 0;
        while ( i < BLOCKS ) {
        occupied_places_.push_back({current_x_.at(i), current_y_.at(i)});
        i++;
        }
        new_tetromino();
    }
}

void MainWindow::new_tetromino()
{
    current_tetromino_.clear();
    current_x_.clear();
    current_y_.clear();

    initialize_tetromino();
}

void MainWindow::end_game()
{
    ui->rightPushButton->setDisabled(true);
    ui->leftPushButton->setDisabled(true);
    ui->downPushButton->setDisabled(true);

    ui->restartPushButton->show();
    ui->restartPushButton->setDisabled(false);

    tempo_.stop();

    QTime* delete_this_time = time_;
    if ( timer_->isActive() ) {
        timer_->stop();

        time_ = nullptr;
        delete delete_this_time;
    }

    ui->gameOverText->setStyleSheet("background: rgba(0,0,255,0%)");
    ui->gameOverText->show();

    occupied_places_.clear();
    current_tetromino_.clear();
    current_x_.clear();
    current_y_.clear();
}

// Checks if the next move is possible and only then returns true value.
bool MainWindow::can_move()
{
    QRectF canvas = scene_->sceneRect();
    int i = 0;
    while ( i < BLOCKS ) {

        if ( !canvas.contains(current_x_.at(i), current_y_.at(i)+SQUARE_SIDE) ) {
            return false;
        }

        std::vector<double> new_coordinates{current_x_.at(i),
                                            current_y_.at(i)+SQUARE_SIDE};
        for ( auto coordinates : occupied_places_ ) {
            if ( coordinates == new_coordinates ) {
                new_coordinates.clear();
                return false;
            }
        }
        i++;
    }
    return true;
}

// Displays the timer.
void MainWindow::tic()
{
    *time_ = time_->addSecs(1);

    ui->secLcdNumber->display(time_->second());
    ui->minLcdNumber->display(time_->minute());
}

void MainWindow::on_rightPushButton_clicked()
{
    int i = 0;
    while ( i < BLOCKS ) {
        if ( current_x_.at(i) >= BORDER_RIGHT-SQUARE_SIDE) {
            return;
        }
        std::vector<double> new_coordinates{current_x_.at(i)+SQUARE_SIDE,
                                            current_y_.at(i)};
        for ( auto coordinates : occupied_places_ ) {
            if ( coordinates == new_coordinates ) {
                new_coordinates.clear();
                return;
            }
        }
        i++;
    }
    i = 0;
    while ( i < BLOCKS ) {
        current_tetromino_.at(i)->moveBy(SQUARE_SIDE, 0);
        current_x_.at(i) += SQUARE_SIDE;
        i++;
    }
}

void MainWindow::on_leftPushButton_clicked()
{
    int i = 0;
    while ( i < BLOCKS ) {
        if ( current_x_.at(i) <= BORDER_LEFT) {
            return;
        }
        std::vector<double> new_coordinates{current_x_.at(i)-SQUARE_SIDE,
                                            current_y_.at(i)};
        for ( auto coordinates : occupied_places_ ) {
            if ( coordinates == new_coordinates ) {
                new_coordinates.clear();
                return;
            }
        }
        i++;
    }
    i = 0;
    while ( i < BLOCKS ) {
        current_tetromino_.at(i)->moveBy(-SQUARE_SIDE, 0);
        current_x_.at(i) -= SQUARE_SIDE;
        i++;
    }
}

void MainWindow::on_downPushButton_clicked()
{
    while ( can_move() ) {
        int i = 0;
        while ( i < BLOCKS ) {
            current_tetromino_.at(i)->moveBy(0, SQUARE_SIDE);
            current_y_.at(i) += SQUARE_SIDE;
            i++;
        }
    }
}

void MainWindow::on_restartPushButton_clicked()
{
    scene_->clear();
    ui->gameOverText->hide();

    time_ = new QTime( 0, 0, 0 );
    if ( !timer_->isActive() ) {
        timer_->start(1000);
    }
    if ( !tempo_.isActive() ) {
        tempo_.start(500);
    }
    ui->restartPushButton->setDisabled(true);
    ui->restartPushButton->hide();

    ui->rightPushButton->setDisabled(false);
    ui->leftPushButton->setDisabled(false);
    ui->downPushButton->setDisabled(false);

    initialize_tetromino();
}
