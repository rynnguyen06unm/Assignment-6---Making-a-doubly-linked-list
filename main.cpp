#include <iostream>
#include "coordinate.h"

void add_coordinate(Coordinate *list_end, float x, float y)
{
  Coordinate *list_beginning = list_end;
  while (list_beginning->previous != nullptr)
    list_beginning = list_beginning->previous;
 
  Coordinate *add = new Coordinate;
  add->x = x;
  add->y = y;
  add->coord_id = list_length(list_beginning);
  add->next = nullptr;
  add->previous = list_end;
 
  list_end->next = add;
}

void forward_display(Coordinate *list_beginning)
{
  for (Coordinate *current_coord = list_beginning; current_coord != nullptr; current_coord = current_coord->next)
    std::cout << " id " << current_coord->coord_id << ": (" << current_coord->x << ", " << current_coord->y << ")\n";
}

void backward_display(Coordinate *list_end)
{
  
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
  
}

int list_length(Coordinate *list_beginning)
{
  int count = 0;
  for (Coordinate *current_coord = list_beginning; current_coord != nullptr; current_coord = current_coord->next)
    count++;
  return count;
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
  
}

int main()
{
  Coordinate *starting = new Coordinate;
  starting->x = 10.0f;
  starting->y = 20.0f;
  starting->coord_id = 0;
  starting->next = nullptr;
  starting->previous = nullptr;
 
  Coordinate *ending = starting;
  add_coordinate(ending, 35.0f, 15.0f);
  ending = ending->next;
  add_coordinate(ending, 62.0f, 48.0f);
  ending = ending->next;
  add_coordinate(ending, 80.0f, 90.0f);
  ending = ending->next;
 
  std::cout << "Created " << list_length(starting) << " coordinates.\n\n";
  std::cout << "Forward display:\n"; forward_display(starting);
  
  return 0;
}
