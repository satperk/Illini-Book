#include <iostream>
#include "illini_book.hpp"
int main() {
  IlliniBook mybook =
      IlliniBook("./example/persons.csv", "./example/relations.csv");
  std::cout << "initalized book" << std::endl;
  bool first_test = mybook.AreRelated(1, 2);
  std::cout << "expected true: " << first_test << std::endl;
  first_test = mybook.AreRelated(3, 2);
  std::cout << "expected true: " << first_test << std::endl;
  first_test = mybook.AreRelated(1, 9);
  std::cout << "expected false: " << first_test << std::endl;
  first_test = mybook.AreRelated(1, 2, "128");
  std::cout << "expected true: " << first_test << std::endl;
  first_test = mybook.AreRelated(1, 2, "124");
  std::cout << "expected false: " << first_test << std::endl;
  first_test = mybook.AreRelated(1, 6, "128");
  std::cout << "expected true: " << first_test << std::endl;
  first_test = mybook.AreRelated(1, 6, "124");
  std::cout << "expected true: " << first_test << std::endl;
  int test = mybook.GetRelated(1, 2);
  std::cout << "expected 1: " << test << std::endl;
  std::cout << "IMPORTANT" << std::endl;
  test = mybook.GetRelated(1, 3);
  std::cout << "expected 1: " << test << std::endl;
  test = mybook.GetRelated(3, 2);
  std::cout << "expected 2: " << test << std::endl;
  test = mybook.GetRelated(1, 9);
  std::cout << "expected -1: " << test << std::endl;
  test = mybook.GetRelated(1, 2, "128");
  std::cout << "expected 1: " << test << std::endl;
  test = mybook.GetRelated(1, 2, "124");
  std::cout << "expected -1: " << test << std::endl;
  test = mybook.GetRelated(1, 6, "128");
  std::cout << "expected 2: " << test << std::endl;
  test = mybook.GetRelated(1, 6, "124");
  std::cout << "expected 1: " << test << std::endl;
  std::vector<int> steps = mybook.GetSteps(1, 1);
  for (int uin : steps) {
    std::cout << uin << ", ";
  }
  std::cout << std::endl;
  steps = mybook.GetSteps(1, 2);
  for (int uin : steps) {
    std::cout << uin << ", ";
  }
  std::cout << std::endl;
  steps = mybook.GetSteps(1, 3);
  for (int uin : steps) {
    std::cout << uin << ", ";
  }
  std::cout << std::endl;
  steps = mybook.GetSteps(9, 1);
  for (int uin : steps) {
    std::cout << uin << ", ";
  }

  std::cout << std::endl;
  steps = mybook.GetSteps(6, 2);
  for (int uin : steps) {
    std::cout << uin << ", ";
  }
  
  std::cout << std::endl;
  test = mybook.CountGroups();
  std::cout << "expected 3: " << test << std::endl;
  test = mybook.CountGroups("128");
  std::cout << "expected 6: " << test << std::endl;
  test = mybook.CountGroups("124");
  std::cout << "expected 6: " << test << std::endl;
  test = mybook.CountGroups("173");
  std::cout << "expected 10: " << test << std::endl;
  test = mybook.CountGroups(std::vector<std::string>{"128", "173"});
  std::cout << "expected 6: " << test << std::endl;
  test = mybook.CountGroups(std::vector<std::string>{"128", "124"});
  std::cout << "expected 3: " << test << std::endl;
}