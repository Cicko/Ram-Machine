#include "RamMachine.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Program.h"

using namespace std;

void menu (RamMachine * machine) {

  unsigned short option = 0;

  while (option != 8) {
    string fileName;

    cout << "============= RAM MACHINE =============" << endl;
    cout << "1. Run program." << endl;
    cout << "2. Run program (trace)." << endl;
    cout << "3. Show program." << endl;
    cout << "4. Show input tape." << endl;
    cout << "5. Change program. (actual: " << machine->getProgramFileName () << ") " << endl;
    cout << "6. Change input tape. (actual: " << machine->getInputFileName () << ") "  << endl;
    cout << "7. Change output tape. (actual: " << machine->getOutputFileName () << ") " << endl;
    cout << "8. Exit" << endl << endl;

    cout << "Select one option {1-6} : " << endl;
    cin >> option;
    cout << endl << endl;

    switch (option) {
      case 1:
        machine->runProgram (false);
        break;
      case 2:
        machine->runProgram (true);
        break;
      case 3:
        system ("clear");
        machine->showProgram ();
        break;
      case 4:
        system ("clear");
        cout << "Input tape content: " << endl;
        machine->showInputTape ();
        break;
      case 5:
        cout << "Select name for the new program file: " ;
        cin >> fileName;
        machine->resetProgram (fileName);
        break;
      case 6:
        cout << "Select name for the new input tape file: " ;
        cin >> fileName;
        machine->resetInTape (fileName);
        break;
      case 7:
        cout << "Select name for the new output tape file: ";
        cin >> fileName;
        machine->resetOutTape (fileName);
        break;
      case 8:
        cout << "Saliendo.." << endl;
        break;
      default:
        cout << "No conozco" << endl;
    }
    cout << "\n\n\n\n";
  }

  cout << endl << "Adios!! " << endl;

}

int main (int argc, char* argv[]) {

  if (argc < 5) {
    cout << endl << "Usage: \n ./RamMachine <inputTape.txt> <outputTape.txt> <program.ram> <Memory-size>" << endl << endl;
    return -1;
  }
  string inTape (argv[1]);
  string outTape (argv[2]);
  string fich (argv[3]);
  int size = atoi (argv[4]);

  RamMachine * myMachine = new RamMachine (inTape, outTape, fich, size);

  menu(myMachine);



  return 0;
}
