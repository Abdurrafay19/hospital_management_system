#pragma once

#include "../entities/Storage.hpp"

class StorageHelper
{
public:
    template <class T>
    static int nextIDFromStorage(Storage<T> &storage)
    {
        int i;
        int maxID;

        maxID = 0;
        for (i = 0; i < storage.size(); i++)
        {
            if (storage.getAll()[i].getID() > maxID)
            {
                maxID = storage.getAll()[i].getID();
            }
        }

        return maxID + 1;
    }
};
