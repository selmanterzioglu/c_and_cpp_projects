#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>

#define PRINT_MATCH false
#define PRINT_SEARCH false


using namespace std;

class Efficiency {
public:
    Efficiency(std::string file_name) : file_name(file_name)
    {
        file.open(this->file_name, ios::in);
        if (!file.is_open())
            std::cout << "file is not open \n";

        string line{};
        while (getline(file, line))
        {
            lib_vector.push_back({get_libs(line)[0], get_libs(line)[1]});
        }
        print_all_vector(true, false, false);

        cout << "vector_size= " << lib_vector.size() << "\n";


        for (int i = 0; i < lib_vector.size(); i++)
        {
            bool is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i);
            if (is_delete)
                lib_vector.erase(lib_vector.begin() + 3);
        }
        print_all_vector(true, false, false);

        cout << "vector_size= " << lib_vector.size() << "\n";

        write_to_file("output.txt");

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

        //"ChannelHandler.h" -> "GmdssEnums.h"

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


    bool match_parent_child(string parent_lib_name, string child_lib_name)
    {
        for (int i = 0; i < lib_parent.size(); i++)
        {
            for (int k = 0; k < lib_child.size(); k++)
            {
                if (lib_child[k][0] == lib_parent[i][1])
                {
                    if (PRINT_MATCH)
                    {
                        cout << "lib_child  index= " << k << "\n";
                        cout << "lib_parent index= " << i << "\n\n";
                    }
                    return true;
                }
            }
        }
        return false;
    }
    bool search_parent_child(string parent_lib_name, string child_lib_name, int parent_id)
    {
        if (PRINT_SEARCH)
        {
            cout << "Searching lib..\n";
            cout << "parent lib = " << parent_lib_name << "\n";
            cout << "child lib  = " << child_lib_name << "\n";
            cout << "index      = " << parent_id << "\n\n";
        }

        for (int i = 0; i < lib_vector.size(); i++)
        {
            if (i == parent_id)
                continue;

            if (lib_vector[i][0] == parent_lib_name)
                lib_parent.push_back(lib_vector[i]);

            for (int k = 0; k < lib_vector[i].size(); k++)
                if (lib_vector[i][k] == child_lib_name)
                    lib_child.push_back(lib_vector[i]);
        }
        return match_parent_child(parent_lib_name, child_lib_name);
    }

    void print_all_vector(bool all_list, bool parent_list, bool child_list)
    {
        if (all_list)
        {
            cout << "*********************\n";
            cout << "All List\n";
            cout << "*********************\n";
            for (int i = 0; i < lib_vector.size(); i++) {
                for (int j = 0; j < lib_vector[i].size(); j++)
                {
                    int size = static_cast <int>(lib_vector[i][j].length());
                    std::cout << "[" << i << "][" << j << "]" << lib_vector[i][j] << setw(50 - size) << " ";
                }
                cout << "\n";
            }
        }
        
        if (parent_list)
        {
            cout << "*********************\n";
            cout << "Parent List\n";
            cout << "*********************\n";
            for (int i = 0; i < lib_parent.size(); i++) {
                for (int j = 0; j < lib_parent[i].size(); j++) {
                    int size = static_cast <int>(lib_vector[i][j].length());
                    std::cout << "[" << i << "][" << j << "]" << lib_parent[i][j] << setw(50 - size) << "\t";
                }
                cout << "\n";
            }
        }
        if (child_list)
        {
            cout << "*********************\n";
            cout << "Child List\n";
            cout << "*********************\n";
            for (int i = 0; i < lib_child.size(); i++) {
                for (int j = 0; j < lib_child[i].size(); j++)
                {
                    int size = static_cast <int>(lib_vector[i][j].length());
                    std::cout << "[" << i << "][" << j << "]" << lib_child[i][j] << setw(50 - size) << "\t";
                }
                cout << "\n";
            }
        }
        cout << "\n\n";

        /*for (int i = 0; i < lib_vector.size(); i++) {
            for (int j = 0; j < lib_vector[i].size(); j++)
                std::cout << lib_vector[i][j] << "\t[" << i << "][" << j << "]\n";
        }*/
    }

private:
    
    vector<vector<string>> lib_vector;// efficient library list
    vector<vector<string>> lib_parent;
    vector<vector<string>> lib_child;

    std::ifstream file;
    std::string file_name{};


    void write_to_file(string output_file_name)
    {
        ofstream output_file(output_file_name);
        if (output_file.is_open())
        {
            for (int i = 0; i < lib_vector.size(); i++) {
                for (int j = 0; j < lib_vector[i].size(); j++)
                {
                    int size = static_cast <int>(lib_vector[i][j].length());
                    if(j== 0)
                        output_file << "\"" << lib_vector[i][j] << "\" -> " << setw(50 - size) << " ";
                    else
                        output_file << "\"" << lib_vector[i][j] << "\"" << setw(50 - size) << " ";

                }
                output_file << "\n";
            }
        }
    }
    std::string get_line_by_line()
    {
        std::string line;
        std::getline(file, line);
        return line;
    }
};

/*


void test()
{
    vector<vector<string>> lib_vector;
    //
    //algoritma alternatifleri
    //mehmet'i iceren bir listeye al.
    //bu listedekilerle test'in icerdiklerini karsilastir.
    //ayni olmasi durumunda mehmet'i sil.

    lib_vector.push_back({ "fatih", "mehmet" });
    lib_vector.push_back({ "ali", "mehmet" });

    lib_vector.push_back({ "test", "ali" });
    lib_vector.push_back({ "test", "fatma" });

    lib_vector.push_back({ "test", "mehmet" });

    //lib_vector.erase(lib_vector.begin() + 2);
}

vector<vector<string>> lib_vector;
vector<vector<string>> lib_parent;
vector<vector<string>> lib_child;

bool match_parent_child(string parent_lib_name, string child_lib_name)
{
    for (int i = 0; i < lib_parent.size(); i++)
    {
        for (int k = 0; k < lib_child.size(); k++)
        {
            if (lib_child[k][0] == lib_parent[i][1])
            {
                if (PRINT_MATCH)
                {
                    cout << "lib_child  index= " << k << "\n";
                    cout << "lib_parent index= " << i << "\n\n";
                }
                return true;
            }
        }
    }
    return false;
}

bool search_parent_child(string parent_lib_name, string child_lib_name, int parent_id)
{
    if (PRINT_SEARCH)
    {
        cout << "Searching lib..\n";
        cout << "parent lib = " << parent_lib_name << "\n";
        cout << "child lib  = " << child_lib_name << "\n";
        cout << "index      = " << parent_id << "\n\n";
    }

    for (int i = 0; i < lib_vector.size(); i++)
    {
        if (i == parent_id)
            continue;

        if (lib_vector[i][0] == parent_lib_name)
            lib_parent.push_back(lib_vector[i]);

        for (int k = 0; k < lib_vector[i].size(); k++)
            if (lib_vector[i][k] == child_lib_name)
                lib_child.push_back(lib_vector[i]);
    }
    return match_parent_child(parent_lib_name, child_lib_name);
}
void test_push_back()
{
    lib_vector.push_back({ "fatih", "mehmet" });
    lib_vector.push_back({ "ali", "mehmet" });
    lib_vector.push_back({ "test", "ali" });
    lib_vector.push_back({ "test", "mehmet" }); // unneccessary 
    lib_vector.push_back({ "test", "ayse" });   // unneccessary 
    lib_vector.push_back({ "fatih", "ayse" });
}

void print_all_vector(bool all_list, bool parent_list, bool child_list)
{
    if (all_list)
    {
        cout << "all list\n";
        for (int i = 0; i < lib_vector.size(); i++) {
            for (int j = 0; j < lib_vector[i].size(); j++)
                std::cout << "[" << i << "][" << j << "]" << lib_vector[i][j] << "\t";
            cout << "\n";
        }
    }
    if (parent_list)
    {
        cout << "\nparent list\n";
        for (int i = 0; i < lib_parent.size(); i++) {
            for (int j = 0; j < lib_parent[i].size(); j++)
                std::cout << "[" << i << "][" << j << "]" << lib_parent[i][j] << "\t";
            cout << "\n";
        }
    }
    if (child_list)
    {
        cout << "\nchild list\n";
        for (int i = 0; i < lib_child.size(); i++) {
            for (int j = 0; j < lib_child[i].size(); j++)
                std::cout << "[" << i << "][" << j << "]" << lib_child[i][j] << "\t";
            cout << "\n";
        }
    }
    cout << "\n\n";

    //for (int i = 0; i < lib_vector.size(); i++) {
    //    for (int j = 0; j < lib_vector[i].size(); j++)
    //        std::cout << lib_vector[i][j] << "\t[" << i << "][" << j << "]\n";
    //}

}

int main()
{
    //std::string line =  "\"ChannelHandler.h\" -> \"GmdssEnums.h\"";
    //Efficiency x("dependency.txt");


    //test_push_back();
    //
    //print_all_vector(true,false,false);

    //for (int i = 0; i < lib_vector.size(); i++)
    //{
    //    bool is_delete = search_parent_child(lib_vector[i][0], lib_vector[i][1], i);
    //    if (is_delete)
    //        lib_vector.erase(lib_vector.begin() + 3);
    //}

    //print_all_vector(true,false,false);
}

*/

int main()
{
    //Efficiency x("dependency.txt");

}