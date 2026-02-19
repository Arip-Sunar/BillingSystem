#pragma once
#include <string>

void  LoadUsers  ();
void  SaveUsers  ();
bool  UserExists (const std::string& name);
bool  CheckLogin (const std::string& name, const std::string& pass);
float CartTotal  ();