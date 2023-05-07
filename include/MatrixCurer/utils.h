#ifndef UTILS_H
#define UTILS_H

namespace std
{
    template <typename T, typename U = T>
    T exchange(T &obj, U &&new_value)
    {
        T old_value = std::move(obj);
        obj = std::forward<U>(new_value);
        return old_value;
    }
}

#endif