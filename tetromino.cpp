#include "tetromino.hh"

Tetromino::Tetromino()
{

}

std::vector<int> Tetromino::choose_tetromino(int index)
{
    tetromino_shapes.push_back(smashboy);
    tetromino_shapes.push_back(hero);
    tetromino_shapes.push_back(teewee);
    tetromino_shapes.push_back(blue_ricky);
    tetromino_shapes.push_back(orange_ricky);
    tetromino_shapes.push_back(cleveland_z);
    tetromino_shapes.push_back(rhode_island_z);

    return tetromino_shapes.at(index);
}
