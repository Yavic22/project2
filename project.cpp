#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <iterator>
using std::ostream_iterator;
#include <algorithm>
using std::min_element;

void print_vector(const vector<string> &v){
    /**************************************
     * prints out a vector with a ", " delimmiter
     * @0 const vector<string> reference to print
     * ***********************************/
    ostream_iterator<string> out(cout, ", ");
    copy(v.begin(), v.end(), out);
}

vector<string> build_vector(ifstream &input) {
    /*****************************************
     * builds the vector for password comparison
     * @0 ifstream reference, passwords.txt
     * @return vector of most common passwords
     * **************************************/
    vector<string> passwords;
    string buffer;
    while(!input.eof()){
        input >> buffer;
        passwords.push_back(buffer);
    }
    return passwords;
}

int find_difference(vector<string> &list, const string &password) {
    /*******************************************************
     * Finds the difference between password given and the
     * most common passwords vectors. Removes all but the best
     * matches from the password vector.
     * @0 vector reference of password list
     * @1 const string reference of word to search for
     * @return int difference in char of best match
     * ****************************************************/
    int difference;
    vector<int> dif_index;
    vector<string> matches;
    for (int i = 0; i < (int)list.size(); i++) {
        if ((int)list[i].size() > (int)password.size()) {
            difference = (int)list[i].size();
        } else {
            difference = (int)password.size();
        }
        for (int j = 0; j < (int)password.size(); j++) {
            if (password[j] == list[i][j]) {
                --difference;
            }
        }
        dif_index.push_back(difference);
    }
    difference = *min_element(dif_index.begin(), dif_index.end());
    for (int i = 0; i < (int)list.size(); i++) {
        if (dif_index[i] == difference) {
            matches.push_back(list[i]);
        }
    }
    list = matches;
    return difference;
}
    
int main() {
    string password;
    vector<string> password_list;
    int char_dif = 0;
    ifstream input("common_passwords.txt");
    cout << "Give me a password:" << endl;
    cin >> password;
    cout << "You provided a password of " << password << endl;
    cout << "The most similar passwords to " << password << " are:" << endl;
    password_list = build_vector(input);
    char_dif = find_difference(password_list, password);
    sort(password_list.begin(), password_list.end());
    print_vector(password_list);
    cout << endl << "All of which are " << char_dif << " character(s) different." << endl;
}

