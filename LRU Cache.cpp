#include<bits/stdc++.h>
using namespace std;

struct entry {
    entry(string k, int v, entry *n, entry *p):
        key(k), value(v), next(n), prev(p){}
    string key;
    int value;
    entry *next;
    entry *prev;
};

struct hash_item {
    hash_item(string k, entry *p):
        key(k), ptr(p){}
    string key;
    entry *ptr;
};

class lru {
public:
    lru(int size):max_size(size), start(NULL), end(NULL){}

    void lookkup(string key)
    {
        map<string, hash_item>::iterator i = hash.find(key);
        if (i != hash.end()) {
            cerr << "Hit, item value: " << i->second.ptr->value << endl;
            entry *hit_entry =  i->second.ptr;
            if(hit_entry!=start){
                if(hit_entry==end){
                    end = end->prev;
                    end->next=NULL;
                    hit_entry->prev=NULL;
                    hit_entry->next=start;
                    start->prev = hit_entry;
                    start = hit_entry;
                }
                else{
                    entry *prev = hit_entry->prev;
                    prev->next = hit_entry->next;
                    prev->next->prev = prev;
                    hit_entry->next = start;
                    hit_entry->prev = NULL;
                    start->prev = hit_entry;
                    start = hit_entry;
                }

            }
        } else {
            if (hash.size() == max_size) {
                cerr << "Missed, cache full, replacing least recently used item: " << end->key << endl;
                entry *endsecond = end->prev;
                hash.erase(end->key);
                delete endsecond->next;
                endsecond->next = NULL;
                end = endsecond;
                entry *new_entry = new entry(key, rand(), NULL, NULL);
                start->prev = new_entry;
                new_entry->next = start;
                start = new_entry;
                hash_item new_item(key, new_entry);
                hash.insert(make_pair(key, new_item));

            } else {
                entry *new_entry = new entry(key, rand(), NULL, NULL);
                cerr << "Missed, cache not full, inserting new item: " << new_entry->key << endl;
                if (start == NULL) {
                    end = new_entry;
                    start = new_entry;
                } else {
                    start->prev = new_entry;
                    new_entry->next = start;
                    start = new_entry;
                }

                hash_item new_item(key, new_entry);
                hash.insert(make_pair(key, new_item));
            }
        }
    }
private:
    map<string, hash_item> hash;
    entry *start;
    entry *end;
    int max_size;
};

int main(int argc, char **argv)
{
    lru cache(3);
    cache.lookkup("key1");
    cache.lookkup("key2");
    cache.lookkup("key3");
    cache.lookkup("key1");
    cache.lookkup("key4");
    cache.lookkup("key4");

    return 0;
}