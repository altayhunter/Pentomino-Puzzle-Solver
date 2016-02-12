# Pentomino Puzzle Solver
The purpose of this project was to solve level 42 of the [Pentomino Puzzle Game](https://play.google.com/store/apps/details?id=kr.junojeong.android.pentomino) app. The empty squares on the board must be filled using each of the 12 [pentominos](https://en.wikipedia.org/wiki/Pentomino) exactly once. The pentominos are allowed to be rotated and flipped.
![Puzzle](https://github.com/altayhunter/Pentomino-Puzzle-Solver/blob/master/puzzle.png)

I had been stuck on this level for well over a year and decided to try my hand at finding a solution programmatically. I came across [this PDF](http://www.cs.brandeis.edu/~storer/JimPuzzles/PACK/Pentominoes/LINKS/PentominoesNivasch.pdf) which explains that these puzzles are equivalent to the [exact cover problem](https://en.wikipedia.org/wiki/Exact_cover#Pentomino_tiling) and details the algorithm used to solve it. The algorithm itself is quite intuitive, but the implementation proved trickier than expected.

I ended up typing in every possible position for every possible piece by hand, a task which was accomplished in about a week. After that my code took about 24 hours to process almost every possible position and came up with the following three solutions:  
![First Solution](https://github.com/altayhunter/Pentomino-Puzzle-Solver/blob/master/solution1.png)
![Second Solution](https://github.com/altayhunter/Pentomino-Puzzle-Solver/blob/master/solution2.png)
![Third Solution](https://github.com/altayhunter/Pentomino-Puzzle-Solver/blob/master/solution3.png)

# Usage
* `make run`

