#pragma once

template <class T>
class Storage {
private:
    T data[100];
    int count;

public:
    Storage();
    ~Storage();

    void add(const T& item);
    void removeByID(int id);
    T* findByID(int id);
    T* getAll();
    int size() const;
};
