#include <cassert>
#include "leveldb/write_batch.h"
#include <iostream>
#include "leveldb/db.h"
#include <stdlib.h>
#include "leveldb/filter_policy.h"
// g++ -o  fir fir.cpp -g -lleveldb -lpthread -I../include/ -L../build/ -std=c++11
using namespace std;

int main(){
	leveldb::DB* db;
	leveldb::Options options;
    const leveldb::FilterPolicy* pfilter = leveldb::NewBloomFilterPolicy(10);
    options.filter_policy = pfilter;
	options.create_if_missing = true;
	options.error_if_exists = false;

	leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
	if (!status.ok()){
		cerr << "Open status:" << status.ToString() << endl;
	}else{
		cout << "Open status:" << status.ToString() << endl;
	}

	string key1 = "key1", key2 = "key2", value = "value";
    leveldb::Status s;
	/*read/write opertions*/
    for(int i = 0; i < 1024; ++i)
    {
		for(int j = 0; j < 1024; ++j)
    	{
			for(int k = 0; k < 1024; ++k) {
				s = db->Put(leveldb::WriteOptions(), 
					key1 + to_string(i) + to_string(j) + to_string(k), 
					value + to_string(i) + to_string(j) + to_string(k));
			}
		}
    }	
	if(!s.ok()){
		cerr << "Put key1 status:" << s.ToString() << endl;
	}
	s = db->Get(leveldb::ReadOptions(), key1, &value);
	if(s.ok()){
		cout << "key1's value:" << value << endl;
		s = db->Put(leveldb::WriteOptions(), key2, value);
		s = db->Get(leveldb::ReadOptions(), key2, &value);
		if(s.ok()){
			cout << "key2's value:" << value << endl;
		}
	}
	else{
		cerr << "Get status:" << s.ToString() << endl;
	}
	if(s.ok()) s = db->Delete(leveldb::WriteOptions(), key1);
	if(!s.ok()){
		cerr << "Delete key1 status:" << s.ToString() << endl;
	}

	/*automic update*/
	s = db->Get(leveldb::ReadOptions(), key1, &value);	
	if(s.ok()){
		leveldb::WriteBatch batch;
		batch.Delete(key1);
		batch.Put(key2, value);
		s = db->Write(leveldb::WriteOptions(), &batch);
		if(!s.ok()){
			cerr << "Batch oprate status:" << s.ToString() << endl;
		}
	}

	/*Iteration*/
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	for(it->SeekToFirst(); it->Valid(); it->Next()){
		cout << it->key().ToString() << ":" << it->value().ToString() << endl;
	}
	assert(it->status().ok());
	delete it;

	/*slice*/
	leveldb::Slice slice;
	if(true)
	{
		string str = "test";
		slice = str;
		cout << "1str addr:" << &str << endl;
		cout << "str value:" << str << endl;
		string* pstr = &str;
		*pstr = "test2";
		cout << "2str addr:" << &str << endl;
		cout << "str value:" << str << endl;
	}
	cout << "slice is:" << slice.ToString()<< endl;
    delete pfilter;
	delete db;
}