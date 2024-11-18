#include <iostream>
#include <string>
#include <vector>

#include "ArgParser.h"

using namespace ArgumentParser;

ArgParser::ArgParser()
    : name_parser_("") {
}

ArgParser::ArgParser(const std::string& name)
    : name_parser_(name) {
}

ArgParser::~ArgParser() {
    for (int i = 0; i < help_info_.size(); ++i) {
        delete help_info_[i]->node_str_pointer;
        delete help_info_[i]->node_int_pointer;
        delete help_info_[i]->node_flag_pointer;
        delete help_info_[i];
    }
}


ArgParser &ArgParser::AddString(const std::string& long_name, const std::string& description, NodeString* new_node) {
    if (long_name != "") {
        map_str_[long_name] = new_node;
        curr_key_.push_back(long_name);
        help_info_[index_help_vec_]->long_name = "--" + long_name;
    }
    if (description != "") {
        map_str_[description] = new_node;
        curr_key_.push_back(description);
        help_info_[index_help_vec_]->description = description;
    }
    help_info_[index_help_vec_]->type = "=<string>";
    help_info_[index_help_vec_]->node_str_pointer = new_node;
    return *this;
}

ArgParser &ArgParser::AddStringArgument(const char& short_name, const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeString* new_node = new NodeString;
    curr_key_.clear();
    if (short_name != '\0') {
        std::string temp_str(1, short_name);
        map_str_[temp_str] = new_node;
        curr_key_.push_back(temp_str);
        help_info_[index_help_vec_]->short_name = '-' + temp_str + ",  ";
    }
    return AddString(long_name, description, new_node);
}

ArgParser &ArgParser::AddStringArgument(const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeString *new_node = new NodeString;
    curr_key_.clear();
    return AddString(long_name, description, new_node);
}


ArgParser &ArgParser::AddInt(const std::string& long_name, const std::string& description, NodeInt* new_node) {
    if (long_name != "") {
        map_int_[long_name] = new_node;
        curr_key_.push_back(long_name);
        help_info_[index_help_vec_]->long_name = "--" + long_name;
    }
    if (description != "") {
        map_int_[description] = new_node;
        curr_key_.push_back(description);
        help_info_[index_help_vec_]->description = description;
    }
    help_info_[index_help_vec_]->type = "=<int>";
    help_info_[index_help_vec_]->node_int_pointer = new_node;
    return *this;
}

ArgParser &ArgParser::AddIntArgument(const char& short_name, const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeInt *new_node = new NodeInt;
    curr_key_.clear();
    if (short_name != '\0') {
        std::string temp_str(1, short_name);
        map_int_[temp_str] = new_node;
        curr_key_.push_back(temp_str);
        help_info_[index_help_vec_]->short_name = '-' + temp_str + ",  ";
    }
    return AddInt(long_name, description, new_node);
}

ArgParser &ArgParser::AddIntArgument(const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeInt *new_node = new NodeInt;
    curr_key_.clear();
    return AddInt(long_name, description, new_node);
}


ArgParser &ArgParser::AddFlagArg(const std::string& long_name, const std::string& description, NodeFlag* new_node) {
    if (long_name != "") {
        map_flag_[long_name] = new_node;
        curr_key_.push_back(long_name);
        help_info_[index_help_vec_]->long_name = "--" + long_name;
    }
    if (description != "") {
        map_flag_[description] = new_node;
        curr_key_.push_back(description);
        help_info_[index_help_vec_]->description = description;
    }
    help_info_[index_help_vec_]->node_flag_pointer = new_node;
    return *this;
}

ArgParser &ArgParser::AddFlag(const char& short_name, const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeFlag *new_node = new NodeFlag;
    curr_key_.clear();
    if (short_name != '\0') {
        std::string temp_str(1, short_name);
        map_flag_[temp_str] = new_node;
        curr_key_.push_back(temp_str);
        help_info_[index_help_vec_]->short_name = '-' + temp_str + ",  ";
    }
    return AddFlagArg(long_name, description, new_node);
}

ArgParser &ArgParser::AddFlag(const std::string& long_name, const std::string& description) {
    ++index_help_vec_;
    help_info_.push_back(new NodeHelpInfo);
    NodeFlag *new_node = new NodeFlag;
    curr_key_.clear();
    return AddFlagArg(long_name, description, new_node);
}


ArgParser &ArgParser::AddHelpArg(const std::string &long_name, const std::string &description) {
    res_help_val_.push_back(long_name);
    res_help_val_.push_back(description);
    return *this;
}

ArgParser &ArgParser::AddHelp(const char &short_name, const std::string &long_name, const std::string &description) {
    curr_key_.clear();
    std::string temp(1, short_name);
    res_help_val_.push_back(temp);
    return AddHelpArg(long_name, description);
}

ArgParser &ArgParser::AddHelp(const std::string &long_name, const std::string &description) {
    curr_key_.clear();
    return AddHelpArg(long_name, description);
}

bool ArgParser::Help() {
    if (res_help_val_.size() != 0) {
        return true;
    }
    return false;
}

std::string ArgParser::HelpDescription() {
    std::string all_help_info = "";
    for (int i = 0; i < help_info_.size(); ++i) {
        all_help_info += help_info_[i]->short_name + help_info_[i]->long_name
                       + help_info_[i]->type + ",  " + help_info_[i]->description
                       + help_info_[i]->default_value + help_info_[i]->multi_value + '\n';
    }
    return name_parser_ + '\n' + "Some Description about program\n\n" + all_help_info + "\n-h, --help Display this help and exit\n";
}


ArgParser &ArgParser::MultiValue(const size_t MinArgsCount) {
    for (auto i: curr_key_) {
        multi_value_[i] = MinArgsCount;
    }
    help_info_[index_help_vec_]->multi_value = " [repeated, min args = " + std::to_string(MinArgsCount) + "] ";
    return *this;
}

bool ArgParser::MinCountValue() {
    size_t count = 0;
    if (multi_value_.size() == 0) {
        return true;
    }
    for (auto i: map_str_) {
        if (multi_value_.find(i.first) != multi_value_.end()) {
            count = multi_value_[i.first];
        } else {
            count = 0;
        }
        if (i.second->to_vec != nullptr && i.second->to_vec->size() < count) {
            return false;
        }
    }
    for (auto i: map_int_) {
        if (multi_value_.find(i.first) != multi_value_.end()) {
            count = multi_value_[i.first];
        } else {
            count = 0;
        }
        if (i.second->to_vec != nullptr && i.second->to_vec->size() < count) {
            return false;
        }
    }

    for (auto i: map_flag_) {
        if (multi_value_.find(i.first) != multi_value_.end()) {
            count = multi_value_[i.first];
        } else {
            count = 0;
        }
        if (i.second->to_vec != nullptr && i.second->to_vec->size() < count) {
            return false;
        }
    }

    return true;
}


ArgParser &ArgParser::StoreValue(std::string& str_value) {
    map_str_[curr_key_[0]]->to_str = &str_value;
    return *this;
}

ArgParser &ArgParser::StoreValue(int& int_value) {
    map_int_[curr_key_[0]]->to_int = &int_value;
    return *this;
}

ArgParser &ArgParser::StoreValue(bool& flag_value) {
    map_flag_[curr_key_[0]]->to_flag = &flag_value;
    return *this;
}


ArgParser &ArgParser::StoreValues(std::vector<std::string>& str_value) {
    map_str_[curr_key_[0]]->to_vec = &str_value;
    return *this;
}

ArgParser &ArgParser::StoreValues(std::vector<int>& int_value) {
    map_int_[curr_key_[0]]->to_vec = &int_value;
    return *this;
}

ArgParser &ArgParser::StoreValues(std::vector<bool>& flag_value) {
    map_flag_[curr_key_[0]]->to_vec = &flag_value;
    return *this;
}


std::string ArgParser::GetStringValue(const std::string& name, const int& index) {
    if (index == -1) {
        return *map_str_[name]->to_str;
    }
    return (*map_str_[name]->to_vec)[index];
}

int ArgParser::GetIntValue(const std::string& name, const int& index) {
    if (index == -1) {
        return *map_int_[name]->to_int;
    }
    return (*map_int_[name]->to_vec)[index];
}

bool ArgParser::GetFlag(const std::string& name, const int& index) {
    if (index == -1) {
        return *(map_flag_[name]->to_flag);
    }
    return (*map_flag_[name]->to_vec)[index];
}


ArgParser &ArgParser::Default(const char* value) {
    *(map_str_[curr_key_[0]]->to_str) = value;
    map_str_[curr_key_[0]]->is_val = true;
    help_info_[index_help_vec_]->default_value = " [default = ";
    help_info_[index_help_vec_]->default_value += value;
    help_info_[index_help_vec_]->default_value += "] ";
    return *this;
}

ArgParser &ArgParser::Default(const int& value) {
    *(map_int_[curr_key_[0]]->to_int) = value;
    map_int_[curr_key_[0]]->is_val = true;
    help_info_[index_help_vec_]->default_value = " [default = " + std::to_string(value) + "] ";
    return *this;
}

ArgParser &ArgParser::Default(const bool& value) {
    *(map_flag_[curr_key_[0]]->to_flag) = value;
    map_flag_[curr_key_[0]]->is_val = true;
    help_info_[index_help_vec_]->default_value = " [default = " + std::to_string(value) + "] ";
    return *this;
}


bool ArgParser::IsAllValue() {
    for (auto i: map_str_) {
        if (i.second->is_val == false) {
            return false;
        }
    }
    for (auto i: map_int_) {
        if (i.second->is_val == false) {
            return false;
        }
    }
    for (auto i: map_flag_) {
        if (i.second->is_val == false) {
            return false;
        }
    }
    return true;
}

ArgParser &ArgParser::Positional() {
    pos_key_ = curr_key_[0];
    return *this;
}


void ArgParser::PushInFlagMap(const std::string& key, bool& is_iter) {
    std::string flag_key;
    for (int i = 0; i < key.size(); ++i) {
        flag_key += key[i];
        if (map_flag_.find(flag_key) != map_flag_.end()) {
            if (map_flag_[flag_key]->to_vec != nullptr) {
                map_flag_[flag_key]->to_vec->push_back(true);
            } else {
                (*(map_flag_[flag_key]->to_flag)) = true;
            }
            map_flag_[flag_key]->is_val = true;
            is_iter = true;
            flag_key = "";
        }
    }
}

void ArgParser::PushInIntMap(const std::string &key, const std::string& value, bool &is_iter) {
    if (map_int_.find(key) != map_int_.end()) {
        if (map_int_[key]->to_vec != nullptr) {
            map_int_[key]->to_vec->push_back(std::stoi(value));
        } else {
            (*map_int_[key]->to_int) = std::stoi(value);
        }
        map_int_[key]->is_val = true;
        is_iter = true;
    }
}

void ArgParser::PushInStringMap(const std::string& key, const std::string value, bool& is_iter) {
    if (map_str_.find(key) != map_str_.end()) {
        if (map_str_[key]->to_vec != nullptr) {
            map_str_[key]->to_vec->push_back(value);
        } else {
            (*map_str_[key]->to_str) = value;
        }
        map_str_[key]->is_val = true;
        is_iter = true;
    }
}

void ArgParser::PushInPos(const std::string& value) {
    if (value == "true") {
        map_flag_[pos_key_]->is_val = true;
        map_flag_[pos_key_]->to_vec->push_back(true);
    } else if (value == "false") {
        map_flag_[pos_key_]->is_val = true;
        map_flag_[pos_key_]->to_vec->push_back(false);
    } else if (value[0] >= '0' && value[0] <= '9') {
        map_int_[pos_key_]->is_val = true;
        map_int_[pos_key_]->to_vec->push_back(std::stoi(value));
    } else {
        map_str_[pos_key_]->is_val = true;
        map_str_[pos_key_]->to_vec->push_back(value);
    }
}


bool ArgParser::Parse(const int& argc, char** &argv) {
    std::vector<std::string> argv_vector;
    for (int i = 0; i < argc; ++i) {
        argv_vector.push_back(argv[i]);
    }
    return Parse(argv_vector);
}

bool ArgParser::Parse(const std::vector<std::string>& argv) {
    for (int i = 1; i < argv.size(); ++i) {
        std::string key_value = pos_key_;
        std::string value = "";
        bool is_iter = false;

        if (argv[i][0] == '-') {
            
            if (argv[i][1] >= '0' && argv[i][1] <= '9') {
                PushInPos(argv[i]);
                continue;
            }           

            int index_start_key = 1;
            if (argv[i][index_start_key] == '-') {
                ++index_start_key;
            }

            if (argv[i].find('=') < argv[i].size()) {
                key_value = argv[i].substr(index_start_key, argv[i].find('=') - index_start_key);
                value = argv[i].substr(argv[i].find('=') + 1);
            } else {
                key_value = argv[i].substr(index_start_key);

                if (std::find(res_help_val_.begin(), res_help_val_.end(), key_value) != res_help_val_.end()) {
                    continue;
                }

                PushInFlagMap(key_value, is_iter);
                if (is_iter) {
                    continue;
                }

                value = argv[i + 1];
                ++i;
            }

            PushInStringMap(key_value, value, is_iter);
            PushInIntMap(key_value, value, is_iter);
            if (is_iter) {
                continue;
            }
            return false;
        }
        PushInPos(argv[i]);
    }

    if (Help()) {
        return true;
    }
    if (!IsAllValue()) {
        return false;
    }
    return MinCountValue();
}
