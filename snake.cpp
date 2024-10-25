#include <iostream>
#include <cstddef>
#include <vector>
#include <conio.h>
#include <list>
#include <random>
#include <cstdlib>
using namespace std;
enum entities { SNAKE = 3,APPLE = 2, EMPTY = 0, WALL = 1};
void render (vector<vector<entities>> &field) {
 for (size_t row = 0; row < field.size();row++) {
  for (size_t column = 0; column < field.size();column++) {
   if (row == 0 || row == field.size() - 1 || column == 0 || column == field.size() - 1) {
    field[row][column] = WALL;
    cout<< "1 ";
    }
   else {
    switch (field[row][column]) {
     case SNAKE: cout<< "X "; break;
     case APPLE: cout<< "@ "; break;
     case EMPTY: cout<< "  "; break;
    }
   }
  }
  cout<< endl;
 }
}
vector<int> apple_spawn (vector<vector<entities>> &field, mt19937 &gen) {
 uniform_int_distribution<> distr(1, 15);
 int random_row = distr(gen);
 int random_column = distr(gen);
 while (field[random_row][random_column] == SNAKE) {
  random_row = distr(gen);
  random_column = distr(gen);
 }
 field[random_row][random_column] = APPLE;
 return {random_row, random_column};
}
void player_move (list<vector<int>> &snake, vector<vector<entities>> &field, char &input) {
 auto head = snake.front();
    switch (input) {
        case 'w':
            head[0]--;
            break;
        case 'a':
            head[1]--;
            break;
        case 's':
            head[0]++;
            break;
        case 'd':
            head[1]++;
            break;
    }
 snake.push_front(head);
 snake.pop_back();
 for (vector<int> &segment : snake) {
  field[segment[0]][segment[1]] = SNAKE;
 }
}
void clear_snake(vector<vector<entities>> &field) {
for (vector<entities> &row: field) {
 for (entities &column : row) {
  if (column == SNAKE) column = EMPTY;
 }
}
}
bool apple_eaten(vector<vector<entities>> &field,list<vector<int>> &snake,vector<int> &apple_location) {
 if (snake.front() == apple_location){
  snake.push_back(apple_location);
  return true;
  }
 else return false;
}
bool check_death (vector<vector<entities>> &field,list<vector<int>> &snake) {
vector <int> front = snake.front();
if(field[front[0]][front[1]] == WALL) return true;
return false;
}
int main () {
 vector<vector<entities>> field {17, vector<entities>(17,EMPTY)};
 list<vector<int>> snake {{8,2}, {8,3}, {8,4}};
 random_device rd;
 bool game_start = false;
 mt19937 gen(rd());
 system("cls");
 cout<< "Hello. this is Snake Game. Use wasd to move. Use q to quit. Have fun!." << endl;
 render(field);
 game_start = true;
 vector<int> apple_location = apple_spawn(field,gen);
 while(game_start) {
 if (check_death(field,snake)){
  game_start = false;
  break;
 }
 char input = _getch();
 if (input == 'q') break;
 clear_snake(field);
 player_move(snake, field, input);
 if (apple_eaten(field,snake,apple_location)) apple_location = apple_spawn(field,gen);
 system("cls");
 render(field);
 }
 }