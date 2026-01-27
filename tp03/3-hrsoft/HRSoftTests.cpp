#include "HRSoft/HRSoftSystem.hpp"

int main() {
  auto system = HRSoftSystem{};

  auto &rd_dpt = system.add_department("R&D");
  auto &market_dpt = system.add_department("Marketing");

  auto &charline = rd_dpt.add_employee("Charline", 6000, nullptr);
  auto &jacques = rd_dpt.add_employee("Jacques", 2500, &charline);
  auto &paul = market_dpt.add_employee("Paul", 2500, &charline);

  // Q2.
  // Affiche différentes informations du système.
  rd_dpt.print_employees();
  system.print_all_departments();
  system.print_all_employees();

  // // Q3.
  // // Affiche tous les employés managés par Charline.
  charline.print_subordinates();

  // // Q4.
  std::cout << "Jacques est licencié..." << std::endl;
  system.remove_employee(jacques);
  rd_dpt.print_employees(); // Jacques ne doit plus apparaître
  charline.print_subordinates(); // Jacques ne doit plus apparaître

  // // Un employée inexistant du système ne devrait pas le faire planter.
  Employee athanase("Athanase", 0);
  system.remove_employee(jacques);
  system.remove_employee(athanase);


  std::cout << "Paul est licencié..." << std::endl;
  // Charline n'a plus de subordonnées, elle ne devrait plus être manager!
  system.remove_employee(paul);
  std::cout << charline << std::endl;

  return 0;
}
