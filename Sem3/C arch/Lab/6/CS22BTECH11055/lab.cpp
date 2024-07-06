#include<bits/stdc++.h>
using namespace std;

class block{
	
private:
	int tag;

public:
	block(int val) : tag(val){}
	int get() {return tag;}
};

string HexToBinary(const string& hexString) {
	
	string binary = "";

    	size_t start = (hexString.size() > 2 && hexString.substr(0, 2) == "0x") ? 2 : 0;

    	for (size_t i = start ; i < hexString.size() ; ++i) {
        	
        	int decimal;

        	if (isdigit(hexString[i])) decimal = hexString[i] - '0';	
            	else decimal = toupper(hexString[i]) - 'A' + 10;

        	binary += bitset<4>(decimal).to_string();
    	}

    	return binary;
}

string Extend(const string& binary) {
    
    int zeros = 32 - binary.length();

    string extended_binary = string(zeros, '0') + binary;

    return extended_binary;
}

int main () {

	int total_hits = 0;
	int total_misses = 0;
        int address_bits = 32;
	int block_size;
	int cache_size;
	int associativity;
	string replace;
	string write;
	string path;
	string line;
	
	cout << "Enter the path to the config file :" << endl;
	getline(cin, path);
	//path = "cache.config";
	
	ifstream config_file(path);
	
	if (!config_file.is_open()) {
		
		cerr << "Error opening the config file " << path << endl;
		return 1;
	}
	
	getline(config_file, line);
	cache_size = stoi(line);
	getline(config_file, line);
	block_size = stoi(line);
	getline(config_file, line);
	associativity = stoi(line);
	getline(config_file, replace);
	getline(config_file, write);
	config_file.close();
	
	int block_bits = (int)(log(block_size) / log(2));
	int index = (associativity > 0 ? (int)(cache_size / (associativity * block_size)) : (int)(cache_size / block_size));
	
	cout << "Enter the path to the access file :" << endl;
	getline(cin, path);
	//path = "trace3.txt";
	
	ifstream access_file(path);
	
	if (!access_file.is_open()) {
		
		cerr << "Error opening the access file " << path << endl;
		return 1;
	}
	
	
	if (associativity > 0) {	
		
		int index_bits = (int)(log(index) / log(2));
		int tag_bits = address_bits - (index_bits + block_bits);
		vector<block> cache[index];
		for (int i = 0 ; i < index ; i++) {
				
			vector<block> set;
			cache[i] = set;
		}
		
		while (getline(access_file, line)) {
			
			bool in_set = 0;
			int mode;
			int word_request_set;
			int word_request_tag;
			string word_request_address;
			mode = (line[0] == 'R' ? 1 : 0);
			word_request_address = Extend(HexToBinary(line.substr(3)));
			word_request_tag = stoul(word_request_address.substr(0, tag_bits), nullptr, 2);
			word_request_set = stoul(word_request_address.substr(tag_bits, index_bits), nullptr, 2);
			
			block processor_call(word_request_tag); 
			
			for (int i = 0 ; i < cache[word_request_set].size() ; i++) {
				
				if (cache[word_request_set].at(i).get() == word_request_tag) {
					
					total_hits++;
					in_set = 1;
					if (replace == "LRU") {
					
						cache[word_request_set].erase(cache[word_request_set].begin() + i);
						cache[word_request_set].push_back(processor_call);
					}
					break;		
				}
			}
			
			if (!in_set) {
				
				total_misses++;
				
				if (mode || write != "WT") {
				
					if (cache[word_request_set].size() < associativity) cache[word_request_set].push_back(processor_call);
					else {
						
						if (replace == "LRU") cache[word_request_set].erase(cache[word_request_set].begin());
						else if (replace == "FIFO") cache[word_request_set].erase(cache[word_request_set].begin());
						else {
							
							random_device seed;
							mt19937 gen(seed());
							
							uniform_int_distribution<int> random(0, cache[word_request_set].size() - 1);	
							cache[word_request_set].erase(cache[word_request_set].begin() + random(gen));	
						}
						
						cache[word_request_set].push_back(processor_call);
					}
				}
			}
				
			cout << "Address : " << line.substr(3) << ", Set : " << hex << showbase << word_request_set << (in_set == 1 ? ", Hit" : ", Miss") << ", Tag : " << hex << showbase << word_request_tag << endl;
		}
	}
	else {
		
		int tag_bits = address_bits - block_bits;
		vector<block> cache;
		
		while (getline(access_file, line)) {
			
			bool in_set = 0;
			int mode;
			int word_request_tag;
			string word_request_address;
			mode = line[0] == 'R' ? 1 : 0;
			word_request_address = Extend(HexToBinary(line.substr(3)));
			word_request_tag = stoul(word_request_address.substr(0, tag_bits), nullptr, 2);
			
			block processor_call(word_request_tag);
			
			for (int i = 0 ; i < cache.size() ; i++) {
				
				if (cache.at(i).get() == word_request_tag) {
					
					total_hits++;
					in_set = 1;
					if (replace == "LRU") {
					
						cache.erase(cache.begin() + i);
						cache.push_back(processor_call);
					}
					break;
				}
			}
			
			if (!in_set) {
				
				total_misses++;
				
				if (mode || write != "WT") {				
					
					if (cache.size() < index) cache.push_back(processor_call);
					else {
					
						if (replace == "LRU") cache.erase(cache.begin());
						else if (replace == "FIFO") cache.erase(cache.begin());
						else {
							
							random_device seed;
							mt19937 gen(seed());
							
							uniform_int_distribution<int> random(0, cache.size() - 1);	
							cache.erase(cache.begin() + random(gen));	
						}
						cache.push_back(processor_call);
					}
					
				}
			}
			
			cout << "Address : " << line.substr(3) << (in_set == 1 ? ", Hit" : ", Miss") << ", Tag : " << hex << showbase << word_request_tag << endl;
		}
	}
	
	cout << "Total hits : " << dec << total_hits << " Total misses : " << dec << total_misses << endl;
	return 0;
}
