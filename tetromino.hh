/* Class: Course
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 *
 * Class that sets the starting coordinates for every tetromino shape that
 * there is in the game.
 *
 * */
#ifndef TETROMINO_HH
#define TETROMINO_HH

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>

class Tetromino
{
public:
    Tetromino();    
    // Retruns one tetromino vector. Vector is choosen by the value of the
    // parameter.
    std::vector<int> choose_tetromino(int index);

private:
    // Contains all the tetrominos.
    std::vector<std::vector<int>> tetromino_shapes;

    // These vectors include coordinates to every block in one tetromino.
    // Index 0 has the first block's x-coordinate, index 1 has the first
    // block's y-coordinate and so on.
    std::vector<int> smashboy = {100, 0, 120, 0, 100, 20, 120, 20};
    std::vector<int> hero = {80, 0, 100, 0, 120, 0, 140, 0};
    std::vector<int> teewee = {100, 0, 80, 20, 100, 20, 120, 20};
    std::vector<int> blue_ricky = {100, 0, 100, 20, 120, 20, 140, 20};
    std::vector<int> orange_ricky = {80, 20, 100, 20, 120, 20, 120, 0};
    std::vector<int> cleveland_z = {80, 0, 100, 0, 100, 20, 120, 20};
    std::vector<int> rhode_island_z = {100, 20, 120, 0, 120, 20, 140, 0};
};

#endif // TETROMINO_HH
