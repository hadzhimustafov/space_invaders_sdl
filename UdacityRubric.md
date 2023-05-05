## Readme:
1. A README with instructions is included with the project.
2. The README indicates which project is chosen
> SpaceInvaders game using SDL2
3. The README includes information about each rubric point addressed
> This file addresses rubric points

## Compiling and testing:
> Project compiles and run using `cmake` and `make`

## Loops, Functions, I/O:
4. The project demonstrates an understanding of C++ functions and control structures.
> `GameScene` class contains variety of loops, functions, lambda functions
5. The project reads data from a file and process the data, or the program writes data to a file.
> Example of file processing can be found in `ScoreManager` class
6. The project accepts user input and processes the input.
> `Game::getUserName()` requests user input to store username in score table

## Object Oriented Programming:
7. The project uses Object-Oriented Programming techniques.
> See `Scene` and `BaseGameObject` classes
8. Classes use appropriate access specifiers for class members.
> `Game` and `BaseGameObject` classes contains variety of different access modifiers
9. Derived class functions override virtual base class functions.
> Class `Obstacle` overrides `BaseGameObject::Draw()` function
10. Templates generalize functions in the project.
> Templates are used in `GameScene::removeDestroyedObjects()` and `GameScene::checkIfBulletHitSomething()`

## Memory Management:
11. The project makes use of references in function declarations.
> `GameScene::removeDestroyedObjects()` and `GameScene::checkIfBulletHitSomething()` accepts reference to vectors
12. The project uses destructors appropriately.
> `BaseGameObject` uses destructor to release SDL_Texture
13. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
> `GameScene` creates game objects using std::make_unique<T>()
14. The project follows the Rule of 5.
> `ScoreEntry` class follows Rule of 5
15. The project uses smart pointers instead of raw pointers.
> `GameScene` uses smart pointer for managing game objects

## Concurrency:
> Concurrency was not used for current project