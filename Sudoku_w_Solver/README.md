# Intro 
This is a sudoku solver application. I didn't want the brute-force backtracking solution to be implemented from the get-go, so I have put together 3 different algorithms for better performance


# STEPS
1. You enter your values with a click and select from pop-up.
2. With every entry, cells on the same block, row, and column update themselves, showing only the remaining possibilities. (This is the removePossibility() process)
3. After entering your initial grid you might see some cells have 1 value, this is because there are not any other possibilities for them during the removePossibility() process
4. removePossibility() only works while setting new values. After that you can proceed with nextStep button executes singleChecker() process (In the source code the method is called checkRepeated() )
5. singleChecker() methods is an update method for all the cells starting from [0][0].
6. Every single cell looks for their row, column and block. If in any one of them, one of the items in possibility list is single, the grid will be set to that value because there are no other place that number can be located.
7. This step can get stuck as well at hard sudoku grids. And at this stage we can implement the backtracking brute-force solution with singleChecker() together.
8. When the "Solve" button is clicked, a recursive functions starts to roll. This function firstly performs singleChecker() method untill it's stuck.
9. After that, from the first row that has more than 1 possibility one of them is selected and the grid is checked for validity.
10. As the main process works with possibility removal, in the deeper levels of recursion wrong answers can be found. If this is the case, the grid is reset to one upper level recursion state and sets the value of next candidate.
11. If the grid is valid and solution is not met, bruteForceSolve() goes one step deeper as expected.
12. As with each step singleChecker() is manually performed while removePossiblity() automatically excludes impossible solutions, our search rate gets way faster.
13. Using this method, my most deepest recursion level is 3, before that usually solver finds the solution and fills the grid.

# Note
This application can not recognise or warn user for unsolvable puzzles, it crashes basically :D
