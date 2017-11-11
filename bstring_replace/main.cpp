#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


#define MAX_BUFFER 200
#define VER "1.0"

using namespace std;

string change_file_name(string file_name){

	int c = file_name.rfind('.');
	string new_file_name;
	if (file_name.npos != c) {
		new_file_name = file_name.substr(0, c) + "__result" + file_name.substr(c);
	} else {
		new_file_name += file_name+"__result";
	}

	cout << new_file_name << endl;

	return new_file_name;
}

int main(int argc, char ** argv) {

	fputs("\n"
		"bstring_replace "VER"\n"
		"by George Imerlishvili\n"
		"e-mail: george.imerlishvili@gmail.com\n"
		"web:    sizeofint.com\n"
		"\n", stdout);

	if (argc < 2) {
		printf("\n"
			"Usage: %s <binary file name>\n"
			"\n", argv[0]);
		exit(1);
	}

	string file_name = argv[1];

	ifstream input(file_name, ios::binary);

	vector<char> buffer((istreambuf_iterator<char>(input)), (istreambuf_iterator<char>()));
	vector<char>::iterator itbegin = buffer.begin();
	vector<char>::iterator itend = buffer.end();

	char needed_str[MAX_BUFFER],
		replace_str[MAX_BUFFER],
		*cp;
	bool somethingChanged = false;
	string yesNo;
	int foundStrLenght;
	cout << "Enter search string:";

	gets_s(needed_str, MAX_BUFFER);


	for (auto it = itbegin; it < itend; it++) {
		cp = nullptr;
		cp = strstr(it._Ptr, needed_str);
		if (cp) {

			foundStrLenght = strnlen(cp, MAX_BUFFER);

			cout << "At address: 0x" << hex << (cp - itbegin._Ptr) << " Found string: " << cp << " Size: " << dec << foundStrLenght << " Bytes" << endl;

			cout << "Change it's value (yes|no)? (no):";

			getline(cin, yesNo);

			if (yesNo == "yes") {

				cout << "Replacment value:";

				gets_s(replace_str, MAX_BUFFER);

				int rpls_str_count = strnlen(replace_str, MAX_BUFFER);

				while (rpls_str_count > foundStrLenght) {
					cout << "Replace value length greater than original! Please enter another value:" << endl;
					gets_s(replace_str, MAX_BUFFER);
					rpls_str_count = strnlen(replace_str, MAX_BUFFER);
				}

				strncpy(cp, replace_str, MAX_BUFFER);
				it += rpls_str_count;
				somethingChanged = true;
			} else {

				it += (cp - it._Ptr);
			}
		}
	}


	if (somethingChanged == true) {
		cout << "Save changes? (yes|no): (yes):";

		getline(cin, yesNo);

		if (yesNo != "no") {
			ofstream ofile(change_file_name(file_name), ios::out | ios::binary);
			ofile.write((char*)&buffer[0], buffer.size() * sizeof(char));
			ofile.close();
			cout << "Done!" << endl;
		}
	}



	return 0;
}
