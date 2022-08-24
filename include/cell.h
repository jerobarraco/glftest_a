#ifndef CELL_H
#define CELL_H

typedef unsigned int dimension;

// might seem silly. but is actually more performant and not hard to understand.
// Only risk is desincronization with the enum. but that's a risk for other methods as well.
static const char CELL_CHARS[] = ".12345678M";

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
	// M9,
	// This is redundant and ambiguous, this will assume the inner mine is counted, while the next doesn't.
    // so for any previous M you could also think that maybe (or maybe not) the inner mine is being counted.
	// This was how the problem was defined but as i understand that would be a logic error.
    MINE,
};

enum CellState{
	CLOSED,
	OPEN,
	FLAGGED
};

#endif // CELL_H
