#include "Program.h"

//#define DEBUG

using namespace std;


Program::Program(string fileName)
{
  load(fileName);
}

Program::~Program()
{

}

void Program::reset(string fileName)
{
  tags_.clear();
  instructions_.clear();
  load(fileName);
}

void Program::load(string fileName) {
  string programStr = readFile(fileName); // read a file and convert it content to a string
  parseInstructions(programStr);
}

// This method allow us to convert file into string
string Program::readFile (string fileName){
  ifstream file;
  string fileData = "";
  fileName_ = fileName;
  file.open (fileName.c_str());
  if (file.is_open()) {
    while (!file.eof()) {
      string temp;
      getline (file,temp);
      fileData += temp + "\n";
    }
    file.close();
  }
  else {
    cerr << "El fichero no existe" << endl;
  }
  return fileData;
}



void  Program::parseInstructions (string fileData) {
  transform(fileData.begin(), fileData.end(), fileData.begin(), ::tolower);   // transform all characters into lower case characters
  vector<string> normalOps = {"add","sub","mul","div","load","store","read","write"};     // Possible no jump operations
  vector<string> jumpOps = {"jump","jgtz","jzero"};  // Possible jump operations
  bool error = false;
  unsigned lineCount = 0;
  char * input = (char*) fileData.c_str(); // Convert string into c char* type
  char * token = std::strtok(input, "\n"); // Divide it into rows
  string actualTag = "main";

  while (token != NULL && !error) {
    bool validInstruction = false;
    bool newTag = false;
    Instruction * dummy = new Instruction;
    string lineStr (token);

    string tag = getTagFromString(lineStr);

    if( tag != "noTag") {
      actualTag = tag;
      tags_.push_back(new Tag(tag, lineCount));
      newTag = true;
    }

    dummy->setTag(actualTag);
    bool skipLine = false;
    fileData = token;
    istringstream iss (fileData);
    string word;
    iss >> word;

    if (newTag) iss >> word;
    if (word == ":") iss >> word;


    if (find (normalOps.begin(), normalOps.end(), word) != normalOps.end()) {   // Is a normal operation
      dummy->setOp(word);
      iss >> word;
      if (word[0] == '*' || word[0] == '=') {                                   // immediate or indirect
        dummy->setType (word[0]);
        if (word.size() > 1) {
          string operand = word.substr (1,word.size()-1);
          dummy->setOperand(operand);
          validInstruction = true;
        }
        else {
           iss >> word;
           if(std::regex_match (word, std::regex("[0-9]") )) {                  // Operand must be a number
             dummy->setOperand(word);
             validInstruction = true;
           }
           else {
             cout << "At line " << lineCount << " is an invalid operad. Expected number and it get \"" << word << "\"." << endl;
             error = true;
           }
        }
      }
      else if (std::regex_match (word, std::regex("[0-9]"))) {
        dummy->setType('d');
        dummy->setOperand(word);
        validInstruction = true;
      }
    }
    else if (find (jumpOps.begin(), jumpOps.end(), word) != jumpOps.end()) {     // Is a jump operation
        dummy->setOp(word);
        iss >> word;
        dummy->setOperand (word);
        validInstruction = true;
    }
    else if (word.find("halt") != string::npos) {                               // Is a halt operation
      dummy->setOp(word);
      validInstruction = true;
    }

    if (validInstruction) {
      dummy->setLine(lineCount++);
      instructions_.push_back(dummy);
    }


    token = std::strtok(NULL, "\n");
  }
}


// This method set all the tags to know what tags exists, so when we parse the instructions
// we will know if that tag exists or not.
/*
void Program::setTags (string code)
{
  unsigned lineCount = 1;
  for (int i = 0; i < code.size(); i++)
  {
    if (code[i] == '\n')
    {
        lineCount++;
    }
    else if (code[i] == ':')      // When we detect Tag
    {
      unsigned short it = i;      // we create iterator to go backwards
      string tag;
      while(code[--it] == ' ' || code[it] == '\t');   // until we search any character to save the tag name
      while(code[it] != ' '  &&   // then we continue saving characters backwards until we reach space again
            code[it] != '\n' &&   // or new line
            code[it] != '\t')     // or tabulator.
      {
          tag.push_back(code[it--]);
      }
      reverse(tag.rbegin(), tag.rend());  // Finally we reverse the characters because we were saving them backwards

      tags_.push_back(new Tag(tag, lineCount));
    }

  }
  for(int i = 0 ; i < tags_.size(); i++)
    cout << "Tags_[" << i << "] = " << tags_[i]->getId() << endl;
}
*/

string Program::getTagFromString(string data) {
    string result = "noTag";
    //cout << "Analize string for tag : " << endl << data << endl;
    if (data.find(":") != string::npos) {                                    // If there is a tag
      for (int i = 0; i < data.size(); i++) {
        if (data[i] == ':'){                                              // When we detect Tag
          int it = i;                                                // we create iterator to go backwards
          string tag;
          while(data[--it] == ' ' || data[it] == '\t' || data[it] == ':');                         // until we search any character to save the tag name
          while(data[it] != ' '  &&                                          // then we continue saving characters backwards until we reach space again
                data[it] != '\t' && it >= 0) {                                          // or tabulator.
             //cout << "We push : data[" << it << "] = " << data[it] << endl;
              tag.push_back(data[it--]);
          }
          reverse(tag.rbegin(), tag.rend());
          result = tag;
        }
      }
    }
    return result;

}



bool Program::reachHalt(unsigned pc) {
  return instructions_[pc]->getOp() == "halt";
}




bool Program::existsTag(string tag)
{
  for(int i = 0; i < tags_.size(); i++) {
    if(tags_[i]->getId() == tag) {
      return true;
    }
  }
  return false;
}

void Program::show() {
  cout << "Tags: " << endl;
  for(int i = 0; i < tags_.size(); i++) {
    tags_[i]->show();
  }
  cout << "===============================" << endl;

  cout << "Instructions: " << endl;
  for(int i = 0; i < instructions_.size(); i++) {
    instructions_[i]->show();
  }
  cout << "===============================" << endl << endl;

  cout << "Pulse Enter para volver al menu..." << endl;
  cin.get();
  cin.get();
  system("clear");
}

int Program::getLineByTag(string tag) {
  for (int i = 0; i < tags_.size(); i++)
    if (tags_[i]->getId() == tag)
      return tags_[i]->getLine();
  return -1;
}

Instruction * Program::getInstruction(unsigned pc)
{
  return instructions_[pc];
}

string Program::getFileName () {
  return fileName_;
}
