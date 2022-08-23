#ifndef CELL_H
#define CELL_H

#endif // CELL_H
typedef unsigned int dimension;

enum Cell {
    EMPTY,
    M1,
    M2,
    M3,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9,
    // This is a bit redundant and ambiguos, this will assume the inner mine is counted, while the next doesnt.
    // so for any previous M you could also think that maybe (or maybe not) the inner mine is being counted.
    // but this is how the problem was defined.
    MINE,
};
