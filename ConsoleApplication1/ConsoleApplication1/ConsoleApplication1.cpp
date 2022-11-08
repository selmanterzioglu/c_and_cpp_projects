#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Efficiency {
public:
    Efficiency(std::string file_name) : file_name(file_name)
    {
        file.open(this->file_name, ios::in);
        if (!file.is_open())
            std::cout << "file is not open \n";
    }

    static std::string* get_libs(std::string line)
    {
        /* 
        // gives libs as a string list like below
        // line = "ChannelHandler.h" -> "GmdssEnums.h";
        // lib1 = ChannelHandler.h 
        // lib2 = GmdssEnums.h
        // return {lib1, lib2};
        */

        size_t point1 = line.find("\"");
        size_t point2 = line.find("\"", point1 + 1);
        size_t point3 = line.find("\"", point2 + 1);
        size_t point4 = line.find("\"", point3 + 1);

        size_t lib1_range = point2 - point1;
        size_t lib2_range = point4 - point3;

        std::string* libs = new std::string[2];

        libs[0] = line.substr(point1 + 1, lib1_range - 1);
        libs[1] = line.substr(point3 + 1, lib2_range - 1);

        return libs;
    }

    int* compare_libs(std::string lib_name)
    {

    }
    void add_libs_first_time(string lib1, string lib2, int idx)
    {
        // This function only works once.
        all_lib_list.push_back({ lib1, lib2 });
        ef_lib_list = all_lib_list; // copy first lib list from file to efficient lib list.
    }

private:
    vector<vector<string>> ef_lib_list; // efficient library list
    vector<vector<string>> all_lib_list;
    std::ifstream file;
    std::string file_name{};

    std::string get_line_by_line()
    {
        std::string line;
        std::getline(file, line);
        return line;
    }
};

int find_head_lib(vector<vector<string>>lib_vector)
{
    return 0;
}
void test()
{
    vector<vector<string>> lib_vector;
    /*
    algoritma alternatifleri
    mehmet'i iceren bir listeye al.
    bu listedekilerle test'in icerdiklerini karsilastir.
    ayni olmasi durumunda mehmet'i sil.
    */

    lib_vector.push_back({ "fatih", "mehmet" });
    lib_vector.push_back({ "ali", "mehmet" });

    lib_vector.push_back({ "test", "ali" });
    lib_vector.push_back({ "test", "fatma" });

    lib_vector.push_back({ "test", "mehmet" }); 

    //lib_vector.erase(lib_vector.begin() + 2);
}
int main()
{
    //std::string line =  "\"ChannelHandler.h\" -> \"GmdssEnums.h\"";
    //Efficiency x("dependency.txt");

    //lib_vector[0].push_back("oglu");

    vector<vector<string>> lib_vector;

    /*
    algoritma alternatifleri
    mehmet'i iceren bir listeye al.
    bu listedekilerle test'in icerdiklerini karsilastir.
    ayni olmasi durumunda mehmet'i sil.
    */

    lib_vector.push_back({"fatih", "mehmet"});

    lib_vector.push_back({"ali", "mehmet"});
    lib_vector.push_back({"test", "ali"});
    lib_vector.push_back({"test", "mehmet"}); // test >> mehmet "delete mehmet"

    lib_vector.erase(lib_vector.begin() + 2);

    //lib_vector.erase(lib_vector.begin() + 2);

    std::string find_text = "deneme";
    
    int max = 0;
    vector<int> temp;

    // find head has max member lib test code
    cout << "\n\n";
    for (int i = 0; i < lib_vector.size(); i++) {
        if (lib_vector[i][0] == find_text)
        {
            temp.push_back(i);
            if (lib_vector[i].size() > max)
                max = i;
            cout << "BULUNDU! [" << i << "]"<< lib_vector[i][0] << "\n";
        }
    }
    cout << "max= " << max << "\n";

    for (int i = 0; i < temp.size(); i++)
    {
        if (i != max) 
            lib_vector.erase(lib_vector.begin() + i);
    }

    for (int i = 0; i < lib_vector.size(); i++) {
        for (int j = 0; j < lib_vector[i].size(); j++)
            std::cout << "[" << i << "][" << j << "]" << lib_vector[i][j] << "\t";
        cout << "\n";
    }

    /*for (int i = 0; i < lib_vector.size(); i++) {
        for (int j = 0; j < lib_vector[i].size(); j++)
            std::cout << lib_vector[i][j] << "\t[" << i << "][" << j << "]\n";
    }*/


}