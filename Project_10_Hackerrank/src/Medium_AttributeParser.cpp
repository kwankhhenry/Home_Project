#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main()
{
    std::ifstream file("input/Medium_AttributeParser_input.txt");
    if(file.is_open())
    {
    int N, Q;
    file >> N >> Q;
    file.ignore();
    
    int TagNum = N, QueryNum = Q;
    string line_string;
    vector<string> tagVect;
    unordered_map<string, string> properties;

    while(TagNum)
    {
        // Get each line (excluding braces <>)
        string data_string;
        string tag_name, attribute_name, value;

        getline(file, line_string);
        //cout << "Analyzing: " << line_string << endl;
        if (line_string.substr(0,2) == "</")
        {
            data_string = line_string.substr(2,line_string.length()-3);

            // Get Tag Name
            stringstream ss(data_string);
            ss >> tag_name;
            ss.ignore();
            getline(ss, data_string);
            //cout << "Tag name is: '" << tag_name << "'" << endl;

            tagVect.pop_back();
        }
        else if (line_string.substr(0,1) == "<")
        {
            data_string = line_string.substr(1,line_string.length()-2);

            // Get Tag Name
            stringstream ss(data_string);
            ss >> tag_name;
            ss.ignore();
            getline(ss, data_string);
            //cout << "Tag name is: '" << tag_name << "'" << endl;

            // Insert into Tag vector
            if(tagVect.size() != 0)
                tag_name = tagVect.back() + '.' + tag_name;
            //cout << "Inserting tag name: " << tag_name << endl;
            tagVect.push_back(tag_name);
        }
 
        // Traverse string
        if(data_string.length() != 0)
        {
            std::size_t found_pos, current_pos;
            string temp_str = data_string;
            
            found_pos = temp_str.find('=');
            while(found_pos != std::string::npos)
            {
                // Obtain attribute - name
                current_pos=0;
                attribute_name = temp_str.substr(current_pos, found_pos);
                attribute_name.erase(std::remove(attribute_name.begin(), attribute_name.end(), ' '), attribute_name.end());
                current_pos = found_pos;
                //cout << "Attribute name is: '" << attribute_name << "'" << endl;
                
                // Obtain attribute - value
                std::size_t start_value_pos, end_value_pos;
                temp_str = temp_str.substr(current_pos);
                start_value_pos = temp_str.find('"');
                end_value_pos = temp_str.find('"', start_value_pos+1);
                value = temp_str.substr(start_value_pos+1, end_value_pos-start_value_pos-1);
                current_pos = end_value_pos;
                //cout << "Value is: '" << value << "'" << endl;

                // Insert into map
                properties.insert(std::pair<string,string>(tag_name+'~'+attribute_name, value));
                //cout << "Inserting " << tag_name+'~'+attribute_name << " = " << value << " into map." << endl;

                // Find next attribute
                temp_str = temp_str.substr(current_pos+1);
                //cout << "new temp str is: '" << temp_str << "'" << endl;
                found_pos = temp_str.find('=');
            }
            //cout << "\n";
        }
        //cout  << "Tag num: " << TagNum << endl;
        TagNum--;
    }
    
    /*for(unordered_map<string,string>::iterator it=properties.begin(); it !=properties.end(); it++)
    {
        cout << "key: " << it->first << ", value: " << it->second << endl;
    }*/

    while(QueryNum)
    {
        getline(file, line_string);
        //cout << "Finding: " << line_string << endl;
        if(properties.find(line_string) != properties.end())
            cout << properties[line_string] << endl;
        else
            cout << "Not Found!" << endl;
        QueryNum--;
    }

    }
    file.close();

    return 0;
}