#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ostream>

// C++ //           :::           // Just //
// int //           :::           // tiv // 
// double //        :::           // dubl //
// bool //          :::           // bool //
// string //        :::           // kalgotka //
// cout //          :::           // hani //
// while //         :::           // qanider //
// if //            :::           // ete //

// c++ //           :::             // Just //
// int x;//         :::             // tiv x; //
// double db; //    :::             // dubl sp; //
// string str; //   :::             // kalgotka g; //
// cout << x; //    :::             // hani <<< g; //
// while() //       :::             // qanider() //
// if() //          :::             // ete() //



struct im_lezu
{
    std::string name;
    char type;
    unsigned short index; 
    bool znacheni;
};


std::vector <std::string> str_var; 

std::vector <int> int_var; 

std::vector <double> doub_var; 

std::vector <bool> bool_var; 

std::vector <im_lezu> im_lezu_var; 

std::vector <std::string> code;
std::vector <std::string> tokens;
std::vector <std::string> qanider;
std::string token;
std::string codie;

int index = 0;

void create(std::vector <std::string>& tokens); 

void repack(std::vector <std::string>& tokens);

void math(std::vector <std::string>& tokens);

void tpel(std::vector <std::string>& tokens);

void declion(std::vector <std::string>& tokens);

void condition(std::vector <std::string>& tokens); 

void traslation(std::string& codie); 

void memory();

int main()
{
    std::string path = "im_srti_interpretator.txt";
    std::ifstream fin;
    fin.open(path);
    if(fin.is_open())
    {
        while(!fin.eof())
        {
            std::string tox;
            std::getline(fin,tox);
            std::string tmp;
            for(int i = 0; i <= tox.length(); ++i)
            {
                if(tox[i] != '\0')
                {
                    tmp += tox[i];
                }
                else
                {
                    code.push_back(tmp); 
                    tmp = "";
                }
            }
        }
    }
    else
    {
        std::cout << "Just Error" << std::endl;
    }

    for(int i = 0; i < code.size(); ++i)
    {
        std::string out = "";
        bool tmp = false;
        for(int j = 0; j < code[i].size(); ++j)
        {
            if(code[i][j] != ' ' && code[i][j] != ' ') tmp = true;
            if(tmp) out += code[i][j];
        }
        code[i] = out;
    }

    for(int i = 0; i < code.size(); ++i)
    {
        std::cout << code[i] << std::endl;
    }


    for( ; index < code.size(); ++index)
    {
        traslation(code[index]);
    }
}

void create(std::vector <std::string>& tokens)
{
    for(int i = 0, ili = 0; i < tokens.size(); ++i, ili++)
    {
        im_lezu I_L;
        I_L.type = tokens[0][0];
        i++;
        if(ili > 0)
        {
            I_L.name = tokens[i-1];
        }
        else
        {
            I_L.name = tokens[i];
        }
        i++;

        if(tokens[i] == "=")
        {
            i++;
        }
        else if(tokens[i] == "," && tokens[i] == ";")
        {
            I_L.znacheni = false;
            im_lezu_var.push_back(I_L);
            continue;
        }
        I_L.znacheni = true;

        if(tokens[0] == "tiv")
        {
            int tmp = std::stoi(tokens[i]);
            I_L.index = int_var.size();
            int_var.push_back(tmp);
        }
        else if(tokens[0] == "kalgotka")
        {
            std::string tmp = tokens[i];
            I_L.index = str_var.size();
            str_var.push_back(tmp);
        }
        else if(tokens[0] == "dubl")
        {
            double tmp = std::stod(tokens[i]);
            I_L.index = doub_var.size();
            doub_var.push_back(tmp);
        }
        else if(tokens[0] == "bool")
        {
            bool tmp;
            if(tokens[i] == "real")
            {
                tmp = true;
            }
            else if(tokens[i] == "fake")
            {
                tmp = false;
            }
            I_L.index = bool_var.size();
            bool_var.push_back(tmp);
        }
        i++;
        im_lezu_var.push_back(I_L);
    }
}

void math(std::vector <std::string>& tokens)
{
    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] == "*" || tokens[i] == "/")
        {
            char simbol = tokens[i][0];
            double db[3];
            db[0] = std::stod(tokens[i-1]);
            db[1] = std::stod(tokens[i+1]);
            tokens.erase(tokens.begin()+ (i-1));
            tokens.erase(tokens.begin() + (i));
            if(simbol == '*')
            {
                db[2] = db[0] * db[1];
            }
            else
            {
                db[2] = db[0] / db[1];
            }
            i--;
            tokens[i] = std::to_string(db[2]);
        }
    }

    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] == "+" || tokens[i] == "-")
        {
            char simbol = tokens[i][0];
            double db[3];
            db[0] = std::stod(tokens[i-1]);
            db[1] = std::stod(tokens[i+1]);
            tokens.erase(tokens.begin()+ (i-1));
            tokens.erase(tokens.begin() + (i));
            if(simbol == '+')
            {
                db[2] = db[0] + db[1];
            }
            else
            {
                db[2] = db[0] - db[1];
            }
            i--;
            tokens[i] = std::to_string(db[2]);
        }
    }
}

void repack(std::vector <std::string>& tokens)
{
    for(int j = 1; j < tokens.size(); ++j)
    {
        for(int i = 0; i < im_lezu_var.size(); ++i)
        {
            if(tokens[j] == im_lezu_var[i].name)
            {
                if(im_lezu_var[i].type == 'm')
                {
                    tokens[j] = std::to_string(int_var[im_lezu_var[i].index]);
                }
            }
            else if(im_lezu_var[i].type == 's')
            {
                tokens[j] = std::to_string(doub_var[im_lezu_var[i].index]);
            }
            else if(im_lezu_var[i].type == 'b')
            {
                tokens[j] = std::to_string(bool_var[im_lezu_var[i].index]);
            }
            else if(im_lezu_var[i].type == 'g')
            {
                tokens[j] = str_var[im_lezu_var[i].index];
            }
        }
    }
}


void declion(std::vector <std::string>& tokens)
{
    int j = 0;
    for(int i = 0; i < im_lezu_var.size(); ++i) if(im_lezu_var[i].name == tokens[0]) j = i;
    if(im_lezu_var[j].znacheni == 0)
    {
        if(im_lezu_var[j].type == 'm')
        {
            im_lezu_var[j].index = int_var.size();
            int tmp = std::stoi(tokens[2]);
            int_var.push_back(tmp);
        }
        else if(im_lezu_var[j].type == 'b')
        {
            im_lezu_var[j].index = bool_var.size();
            bool tmp;
            if(tokens[2] == "real") tmp = true;
            else if(tokens[2] == "fake") tmp = false;
            bool_var.push_back(tmp);
        }
        else if(im_lezu_var[j].type == 's')
        {
            im_lezu_var[j].index = doub_var.size();
            double tmp = std::stod(tokens[2]);
            doub_var.push_back(tmp);
        }
        else if(im_lezu_var[j].type == 'g')
        {
            im_lezu_var[j].index = str_var.size();
            std::string tmp = tokens[2];
            str_var.push_back(tmp);
        }
        im_lezu_var[j].znacheni = true;
    }
    else
    {
        if(im_lezu_var[j].type == 'm')
        {
            int_var[im_lezu_var[j].index] = std::stoi(tokens[2]);
        }
        else if(im_lezu_var[j].type == 's')
        {
            doub_var[im_lezu_var[j].index] = std::stod(tokens[2]);
        }
        else if(im_lezu_var[j].type == 'g')
        {
            str_var[im_lezu_var[j].index] = tokens[2];
        }
        else if(im_lezu_var[j].type == 'b')
        {
            if(tokens[2] == "real")
            {
                bool_var[im_lezu_var[j].index] = 1;
            }
            else if(tokens[2] == "fake")
            {
                bool_var[im_lezu_var[j].index] = 0;
            }
        }
    }
}

void memory()
{
    for(int i = 0; i < im_lezu_var.size(); ++i)
    {
        std::cout << "Name: " << im_lezu_var[i].name << " Type: " << im_lezu_var[i].type << " znacheni: " << im_lezu_var[i].znacheni;
        if(im_lezu_var[i].znacheni == 1)
        {
            std::cout << "Value: " ;
            if(im_lezu_var[i].type == 'm') 
            {
                std::cout << int_var[im_lezu_var[i].index] << std::endl;
            }
            else if(im_lezu_var[i].type == 's')
            {
                std::cout << doub_var[im_lezu_var[i].index] << std::endl;
            }
            else if(im_lezu_var[i].type == 'b')
            {
                std::cout << bool_var[im_lezu_var[i].index] << std::endl;
            }
            else if(im_lezu_var[i].type == 'g')
            {
                std::cout << str_var[im_lezu_var[i].index] << std::endl;
            }
        }
        else
        {
            std::cout << "Raven" << std::endl;
        }
    }
}

void tpel(std::vector <std::string>& tokens)
{
    int i = 0;
    if(tokens[i] == "hani")i++;
    else if (tokens[i] == "<<<" || tokens[i] == "<<<") { repack(tokens); math(tokens); }
    else
    {
        i++;
        for( ; i < tokens.size()-1; ++i) std::cout << tokens[i] << " ";
    }
    i += 2;
    for( ; i < tokens.size() - 1; ++i) std::cout << token[i] << " ";
    //std::cout << std::endl; 
}

void condition(std::vector <std::string>& tokens)
{
    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] == ">" || tokens[i] == ">=" || tokens[i] == "<" || tokens[i] == "<=" || tokens[i] == "==" || tokens[i] == "!=")
        {
            std::string wre = tokens[i];
            double db[3];
            db[0] = std::stod(tokens[i-1]);
            db[1] = std::stod(tokens[i+1]);
            tokens.erase(tokens.begin() + (i-1));
            tokens.erase(tokens.begin() + (i));
            if(wre == ">") db[2] = db[0] > db[1];
            else if(wre == ">=") db[2] = db[0] >= db[1];
            else if(wre == "<") db[2] = db[0] < db[1];
            else if(wre == "<=") db[2] = db[0] <= db[1];
            else if(wre == "==") db[2] = db[0] == db[1];
            else if(wre == "!=") db[2] = db[0] != db[1];
            i--;
            tokens[i] = std::to_string(db[2]);
        }
    }

    for(int i = 0; i < tokens.size(); ++i)
    {
        if(tokens[i] == "&&" || tokens[i] == "||")
        {
            char wre = tokens[i][0];
            double db[3];
            db[0] = std::stod(tokens[i-1]);
            db[1] = std::stod(tokens[i+1]);
            tokens.erase(tokens.begin() + (i-1));
            tokens.erase(tokens.begin() + (i));
            if(wre == '&') db[2] = db[0] && db[1];
            else if(wre == '|') db[2] = db[0] || db[1];
            i--;
            tokens[i] = std::to_string(db[2]);
        }
        
    }
}


void traslation(std::string& codie)
{
    for(int i = 0; i <= codie.length(); ++i)
    {
        if(codie[i] != ' ' && codie[i] != '\0') token += codie[i];
        else 
        {
            tokens.push_back(token);
            token = "";
        }
        if(tokens[0] == "tiv" || tokens[0] == "dubl" || tokens[0] == "bool" || tokens[0] == "kalgotka")
        {
            repack(tokens);
            math(tokens);
            create(tokens);
        }
        else if(tokens[0] == "hani")
        {
            tpel(tokens);
        }
        else if(tokens[0] == "ete")
        {
            int begin = index, finish = index + 1, count = 0;
            bool tmp = true;
            for( ; tmp ; finish++)
            {
                if(code[finish] == "start")
                {
                    count++;
                }
                else if(code[finish] == "end")
                {
                    count--;
                }
                if(count == 0) tmp = false;
            }
            finish--;
            index++;
            repack(tokens);
            math(tokens);
            condition(tokens);

            if ( std::stoi(tokens[2]) == 1)
		    {
			for (; index < finish; index++)
			    {
				tokens.clear();
				codie = "";
				traslation(code[index]);
			    }
		    }
            index = finish;
        }
        else if(tokens[0] == "qanider")
        {
            int begin = index, finish = index + 1, count = 0;
		    bool tmp = true;
            for( ; tmp ; finish++)
            {
                if(code[finish] == "start")
                {
                    count++;
                }
                else if(code[finish] == "end")
                {
                    count--;
                }
                if(count == 0) tmp = false;
            }
            finish--;
            for( ; begin <= finish; begin++)
            {
                qanider.push_back(code[begin]);
            }
            begin = index;
            tmp = false;
            repack(tokens);
		    math(tokens);
		    condition(tokens);
            if(std::stoi(tokens[2]) == 1) tmp = true;
            while(tmp)
            {
                for(int j = index; j < finish; ++j)
                {
                    tokens.clear();
                    codie = "";
                    traslation(code[j]);
                }

                tokens.clear();
                codie = "";
                for (int i = begin, j = 0; i < finish; i++, j++)
			    {
				    code[i] = qanider[j];
			    }
                codie = code[index];
                for(int i = 0; i <= codie.size(); ++i)
                {
                    if(codie[i] != ' ' && codie[i] != '\0') token += codie[i];
                    else {tokens.push_back(token); token = "";}
                }
                repack(tokens);
			    math(tokens);
			    condition(tokens);

                if (std::stoi(tokens[2]) == 1) tmp = true;
			    else tmp = false;
            }
            index = finish;
        }
        else if(tokens[0] == "memory")
        {
            memory();
        }
        else
        {
            bool tmp = false;
            for(int i = 0; i < im_lezu_var.size(); ++i)
            {
                if(tokens[i] == im_lezu_var[i].name)
                    tmp = true;
            }
            if(tmp == true)
            {
                repack(tokens);
			    math(tokens);
			    declion(tokens);
            }
        }
        tokens.clear();
        codie = "";
    }
}