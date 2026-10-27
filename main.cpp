#include <iostream>
#include "coordinate.h"
#include <cmath>
#include <cstdlib>

// add's a coordinate to the end of the linked list
void add_coordinate(Coordinate *list_end, float x, float y)
{
  Coordinate *list_beginning = list_end;
  while (list_beginning->previous != nullptr)
    list_beginning = list_beginning->previous;

  Coordinate *add = new Coordinate;
  add->x = x;
  add->y = y;
  add->coord_id = list_length(list_beginning); // coordinate id automatically incremented based on length of list 
  add->next = nullptr;
  add->previous = list_end;

  list_end->next = add;
}

// displays all coordinates from beginning to end
void forward_display(Coordinate *list_beginning)
{
  for (Coordinate *current_coord = list_beginning; current_coord != nullptr; current_coord = current_coord->next)
    std::cout << " id " << current_coord->coord_id << ": (" << current_coord->x << ", " << current_coord->y << ")\n";
}

// displays all coordinates from end to beginning
void backward_display(Coordinate *list_end)
{
  for (Coordinate *current_coord = list_end; current_coord != nullptr; current_coord = current_coord->previous)
    std::cout << " id " << current_coord->coord_id << ": (" << current_coord->x << ", " << current_coord->y << ")\n";
}

// removes a coordinate from the linked list
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
  Coordinate *target_coord = list_beginning;
  while (target_coord != nullptr && target_coord->coord_id != coord_id_to_delete)
    target_coord = target_coord->next;

  if (target_coord == nullptr)
    return;

  target_coord->previous->next = target_coord->next;
  if (target_coord->next != nullptr)
    target_coord->next->previous = target_coord->previous;
  delete target_coord;
}

// return the length of the list
int list_length(Coordinate *list_beginning)
{
  int count = 0;
  for (Coordinate *current_coord = list_beginning; current_coord != nullptr; current_coord = current_coord->next)
    count++;
  return count;
}

// find the coordinate that is closest to the given x, y and output the distance between the 2
void closest_to(Coordinate *list_beginning, float x, float y)
{
  Coordinate *closest = list_beginning;
  float dx = closest->x - x;
  float dy = closest->y - y;
  float closest_squared = dx * dx + dy * dy;

  for (Coordinate *current_coord = list_beginning->next; current_coord != nullptr; current_coord = current_coord->next)
  {
    dx = current_coord->x - x;
    dy = current_coord->y - y;
    float d2 = dx * dx + dy * dy;
    if (d2 < closest_squared)
    {
      closest_squared = d2;
      closest = current_coord;
    }
  }

  std::cout << "Closest to (" << x << ", " << y << ") is id " << closest->coord_id << " at (" << closest->x << ", " << closest->y << "), distance " << std::sqrt(closest_squared) << "\n";
}

int main(int argc, char *argv[])
{
  // random number generator 
  srand(time(nullptr));

  // add coordinates, start with id 0 
  Coordinate *starting = new Coordinate;
  starting->x = rand() / (RAND_MAX / 100.0f); // random x for id 0 coordinate
  starting->y = rand() / (RAND_MAX / 100.0f); // random y for id 0 coordinate
  starting->coord_id = 0;
  starting->next = nullptr;
  starting->previous = nullptr;
  
  // add coordinates, id 1-9  
  Coordinate *ending = starting;
  for (int i = 1; i < atoi(argv[1]); i++)
  {
    float x = rand() / (RAND_MAX / 100.0f); // random x for id 1-9 coordinate
    float y = rand() / (RAND_MAX / 100.0f); // random y for id 1-9 coordinate
    add_coordinate(ending, x, y);
    ending = ending->next;
  }

  // display the list 
  std::cout << "Created " << list_length(starting) << " coordinates.\n\n";
  std::cout << "Forward display:\n"; forward_display(starting); std::cout << "\n";
  std::cout << "Backward display:\n"; backward_display(ending); std::cout << "\n";
  closest_to(starting, 50.0f, 50.0f); std::cout << "\n"; // closest check to middle of 0-100 range, (50, 50)   

  // deletes coordinate id 5 and displays updated list 
  int id_to_delete = 5;
  std::cout << "Deleting id " << id_to_delete << "\n"; delete_coordinate(starting, id_to_delete);
  std::cout << "List length is now " << list_length(starting) << ".\n\n";
  std::cout << "Forward display after delete:\n"; forward_display(starting); std::cout << "\n";
  closest_to(starting, 50.0f, 50.0f); // closest check to middle of 0-100 range, (50, 50)  

  // deletes remaining nodes and frees memory   
  while (starting != nullptr)
  {
    Coordinate *next = starting->next;
    delete starting;
    starting = next;
  }

  return 0;
}
