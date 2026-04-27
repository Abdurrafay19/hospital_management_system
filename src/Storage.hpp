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

template <class T>
Storage<T>::Storage() {
    count = 0;
}

template <class T>
Storage<T>::~Storage() {
    count = 0;
}

template <class T>
void Storage<T>::add(const T& item) {
    if (count >= 100) {
        return;
    }

    data[count] = item;
    count++;
}

template <class T>
void Storage<T>::removeByID(int id) {
    int i;
    int j;

    for (i = 0; i < count; i++) {
        if (data[i].getID() == id) {
            for (j = i; j < count - 1; j++) {
                data[j] = data[j + 1];
            }

            count--;
            return;
        }
    }
}

template <class T>
T* Storage<T>::findByID(int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (data[i].getID() == id) {
            return &data[i];
        }
    }

    return nullptr;
}

template <class T>
T* Storage<T>::getAll() {
    return data;
}

template <class T>
int Storage<T>::size() const {
    return count;
}
